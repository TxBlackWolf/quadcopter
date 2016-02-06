////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       06.02.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "EmulatorDockWidget.h"
#include "ui_EmulatorDockWidget.h"

EmulatorDockWidget::EmulatorDockWidget(QWidget* parent)
    : QDockWidget(parent)
    , m_ui(new Ui::EmulatorDockWidget())
{
    m_ui->setupUi(this);
}

EmulatorDockWidget::~EmulatorDockWidget()
{
    delete m_ui;
}
