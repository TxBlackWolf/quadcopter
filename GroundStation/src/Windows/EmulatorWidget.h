////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       08.02.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef EMULATORWIDGET_H
#define EMULATORWIDGET_H

#include "command/command_emulator.h"
#include "Misc/SubsystemsStatus.h"

#include <QWidget>

#include <cstdint>

namespace Ui {
    class EmulatorWidget;
}

class EmulatorWidget : public QWidget {
    Q_OBJECT

public:
    explicit EmulatorWidget(QWidget* parent = nullptr);
    virtual ~EmulatorWidget();

signals:
    void emulatorStatus(SubsystemStatus);

private:
    void init();
    void initCommandsFramework();
    static void gpioCallback(uint8_t* buffer, uint32_t size);

    void gpioPort4Handler(EmulatorCommandGPIO_t *gpioCommand);
    void setStrobeLight(bool enabled);

private:
    Ui::EmulatorWidget* m_ui;
};

#endif
