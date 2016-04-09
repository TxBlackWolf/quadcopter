////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       08.02.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "EmulatorWidget.h"
#include "ui_EmulatorWidget.h"

#include "common/commands/commands.h"
#include "common/commands/emulator.h"
#include "Tools/Options/CommandsOptions.h"

#include <string>

static EmulatorWidget* globalEmulatorWidget = nullptr;

EmulatorWidget::EmulatorWidget(QWidget* parent)
    : QWidget(parent)
    , m_ui(new Ui::EmulatorWidget())
{
    m_ui->setupUi(this);
    init();

    globalEmulatorWidget = this;
}

EmulatorWidget::~EmulatorWidget()
{
    delete m_ui;
}

void EmulatorWidget::init()
{
    initCommandsFramework();
}

void EmulatorWidget::initCommandsFramework()
{
    command_registerEmulatorCallback(EMULATED_DEVICE_GPIO, &EmulatorWidget::gpioCallback);
}

void EmulatorWidget::gpioCallback(uint8_t* buffer, uint32_t size)
{
    /// @todo Implement.
}
