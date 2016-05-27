////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       23.05.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef PADDRIVER_H
#define PADDRIVER_H

#include <QObject>
#include <QString>
#include <QThread>

#include <cstdint>
#include <linux/input.h>
#include <string>

#define AXIS_MAP_SIZE       (ABS_MAX + 1)
#define KEY_MAX_SMALL       0x1FF
#define KEY_MAX_LARGE       0x2FF
#define BUTTON_MAP_SIZE     (KEY_MAX_LARGE - BTN_MISC + 1)

class PadDriver : public QThread {
    Q_OBJECT

public:
    PadDriver();
    virtual ~PadDriver();

    void run();

signals:
    void detectedPadController(QString name);
    void padControllerAxisPressed(QString name, int value);
    void padControllerButtonPressed(QString name, int value);

public slots:
    void connect(QString device);
    void disconnect();

private:
    void getButtonsMap();

private:
    bool m_connected;
    int m_controllerFd;

    std::string m_name;
    uint8_t m_axesMap[AXIS_MAP_SIZE];
    uint16_t m_buttonsMap[BUTTON_MAP_SIZE];
};

#endif
