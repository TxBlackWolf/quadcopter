////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       23.05.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "PadController.h"

#include <QTime>

#include <cerrno>
#include <fcntl.h>
#include <linux/joystick.h>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>

#define PAD_NAME_SIZE                           128
#define PAD_CONTROLLER_CONNECT_DELAY_MS         500

// The following values come from include/joystick.h in the kernel source.
#define JSIOCSBTNMAP_LARGE                      _IOW('j', 0x33, __u16[KEY_MAX_LARGE - BTN_MISC + 1])
#define JSIOCSBTNMAP_SMALL                      _IOW('j', 0x33, __u16[KEY_MAX_SMALL - BTN_MISC + 1])
#define JSIOCGBTNMAP_LARGE                      _IOR('j', 0x34, __u16[KEY_MAX_LARGE - BTN_MISC + 1])
#define JSIOCGBTNMAP_SMALL                      _IOR('j', 0x34, __u16[KEY_MAX_SMALL - BTN_MISC + 1])

static const char *AXIS_NAMES[ABS_MAX + 1] = {
    "X", "Y", "Z", "Rx", "Ry", "Rz", "Throttle", "Rudder", "Wheel", "Gas", "Brake", "?", "?", "?", "?", "?",
    "Hat0X", "Hat0Y", "Hat1X", "Hat1Y", "Hat2X", "Hat2Y", "Hat3X", "Hat3Y", "?", "?", "?", "?", "?", "?", "?",
};

static const char *BUTTON_NAMES[KEY_MAX - BTN_MISC + 1] = {
    "Btn0", "Btn1", "Btn2", "Btn3", "Btn4", "Btn5", "Btn6", "Btn7", "Btn8", "Btn9", "?", "?", "?", "?", "?", "?",
    "LeftBtn", "RightBtn", "MiddleBtn", "SideBtn", "ExtraBtn", "ForwardBtn", "BackBtn", "TaskBtn", "?", "?", "?",
    "?", "?", "?", "?", "?", "Trigger", "ThumbBtn", "ThumbBtn2", "TopBtn", "TopBtn2", "PinkieBtn", "BaseBtn", "BaseBtn2",
    "BaseBtn3", "BaseBtn4", "BaseBtn5", "BaseBtn6", "BtnDead", "BtnA", "BtnB", "BtnC", "BtnX", "BtnY", "BtnZ", "BtnTL",
    "BtnTR", "BtnTL2", "BtnTR2", "BtnSelect", "BtnStart", "BtnMode", "BtnThumbL", "BtnThumbR", "?", "?", "?", "?", "?",
    "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "WheelBtn", "Gear up"
};

PadController::PadController()
    : m_connected(false)
    , m_controllerFd(-1)
{
    m_name.resize(PAD_NAME_SIZE);
}

PadController::~PadController()
{
    try {
        disconnect();
    }
    catch(...) {}
}

void PadController::connect(QString device)
{
    if (m_connected) {
        disconnect();
        return;
    }

    if ((m_controllerFd = open(device.toStdString().c_str(), O_RDONLY)) < 0)
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

    emit detectedPadController(m_name.c_str());
    m_connected = true;

    start();
}

void PadController::disconnect()
{
    if(!m_connected)
        return;

    m_connected = false;
    usleep(1000);

    if(m_controllerFd > 0)
        close(m_controllerFd);

    m_controllerFd = -1;
}

void PadController::getButtonsMap()
{
    long ioctls[] = { JSIOCGBTNMAP, JSIOCGBTNMAP_LARGE, JSIOCGBTNMAP_SMALL, 0 };

    // Try each ioctl in turn.
    for (int i = 0; ioctls[i]; ++i) {
        if (ioctl(m_controllerFd, ioctls[i], m_buttonsMap) >= 0) {
            // The ioctl did something.
            break;
        } else if (errno != -EINVAL) {
            // Some other error occurred.
            break;
        }
    }
}

#include <QDebug>
void PadController::run()
{
    QTime timer;
    timer.start();

    while(m_connected) {
        struct js_event js;
        if (read(m_controllerFd, &js, sizeof(struct js_event)) != sizeof(struct js_event))
            continue;

        if(timer.elapsed() < PAD_CONTROLLER_CONNECT_DELAY_MS)
            continue;

        switch(js.type & ~JS_EVENT_INIT) {
        case JS_EVENT_AXIS:
            emit padControllerAxisPressed(AXIS_NAMES[js.number], js.value);
            qDebug() << "Axis: [" << AXIS_NAMES[js.number] << "] = " << js.value;

            break;

        case JS_EVENT_BUTTON:
            emit padControllerButtonPressed(BUTTON_NAMES[js.number], js.value);
            qDebug() << "Button: [" << BUTTON_NAMES[js.number] << "] = " << js.value;
            break;
        }
    }
}
