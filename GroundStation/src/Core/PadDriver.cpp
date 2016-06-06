////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       23.05.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "PadDriver.h"
#include "PadCalibrator.h"

#include <QTime>

#include <cerrno>
#include <fcntl.h>
#include <linux/joystick.h>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>

#define PAD_NAME_SIZE                           32
#define PAD_CONTROLLER_CONNECT_DELAY_MS         500

// The following values come from include/joystick.h in the kernel source.
#define JSIOCSBTNMAP_LARGE                      _IOW('j', 0x33, __u16[KEY_MAX_LARGE - BTN_MISC + 1])
#define JSIOCSBTNMAP_SMALL                      _IOW('j', 0x33, __u16[KEY_MAX_SMALL - BTN_MISC + 1])
#define JSIOCGBTNMAP_LARGE                      _IOR('j', 0x34, __u16[KEY_MAX_LARGE - BTN_MISC + 1])
#define JSIOCGBTNMAP_SMALL                      _IOR('j', 0x34, __u16[KEY_MAX_SMALL - BTN_MISC + 1])

PadDriver::PadDriver()
    : m_connected(false)
    , m_controllerFd(-1)
{
    m_name.resize(PAD_NAME_SIZE);
}

PadDriver::~PadDriver()
{
    try {
        disconnect();
    }
    catch(...) {}
}

void PadDriver::connect(QString device)
{
    if(m_connected) {
        disconnect();
        return;
    }

    if((m_controllerFd = open(device.toStdString().c_str(), O_RDONLY)) < 0)
        return;

    unsigned int axesCount = 0;
    unsigned int buttonsCount = 0;

    ioctl(m_controllerFd, JSIOCGAXES, &axesCount);
    ioctl(m_controllerFd, JSIOCGBUTTONS, &buttonsCount);
    ioctl(m_controllerFd, JSIOCGNAME(m_name.size()), m_name.data());

    // Get axes and button maps.
    ioctl(m_controllerFd, JSIOCGAXMAP, m_axesMap);
    getButtonsMap();

    // Determine whether the button map is usable.
    for(unsigned int i = 0; i < buttonsCount; ++i) {
        if(m_buttonsMap[i] < BTN_MISC || m_buttonsMap[i] > KEY_MAX)
            return;
    }

    m_calibrator = IPadCalibrator::create(m_name);
    emit detectedPadController(m_name.c_str());
    m_connected = true;

    start();
}

void PadDriver::disconnect()
{
    if(!m_connected)
        return;

    m_connected = false;
    usleep(1000);

    if(m_controllerFd > 0)
        close(m_controllerFd);

    m_controllerFd = -1;
}

void PadDriver::setSensitivity(int sensitivity)
{
    if(m_calibrator)
        m_calibrator->setSensitivity(sensitivity);
}

void PadDriver::getButtonsMap()
{
    long ioctls[] = { JSIOCGBTNMAP, JSIOCGBTNMAP_LARGE, JSIOCGBTNMAP_SMALL, 0 };

    // Try each ioctl in turn.
    for(int i = 0; ioctls[i]; ++i) {
        if(ioctl(m_controllerFd, ioctls[i], m_buttonsMap) >= 0) {
            // The ioctl did something.
            break;
        } else if(errno != -EINVAL) {
            // Some other error occurred.
            break;
        }
    }
}

void PadDriver::run()
{
    QTime timer;
    timer.start();

    int axesAngles[AXES_MAX_COUNT] = { 0 };
    bool buttonsStates[BUTTONS_MAX_COUNT] = { false };

    while(m_connected) {
        struct js_event js;
        if(read(m_controllerFd, &js, sizeof(struct js_event)) != sizeof(struct js_event))
            continue;

        // This delay will prevent from initial axis movement readings.
        if(timer.elapsed() < PAD_CONTROLLER_CONNECT_DELAY_MS)
            continue;

        switch(js.type & ~JS_EVENT_INIT) {
        case JS_EVENT_AXIS: {
                int anglePerc = m_calibrator->normalizeAxisAngle(js.value);
                if(axesAngles[js.number] == anglePerc)
                    break;

                axesAngles[js.number] = anglePerc;
                emit padControllerAxisPressed(js.number, anglePerc);
            }
            break;

        case JS_EVENT_BUTTON: {
                bool buttonState = m_calibrator->normalizeButtonState(js.value);
                if(buttonsStates[js.number] == buttonState)
                    break;

                buttonsStates[js.number] = buttonState;
                emit padControllerButtonPressed(js.number, buttonState);
            }
            break;
        }
    }
}
