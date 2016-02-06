////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       06.02.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "EmulatorTabWidget.h"
#include "ui_EmulatorTabWidget.h"

EmulatorTabWidget::EmulatorTabWidget(QWidget *parent)
    : QTabWidget(parent)
    , m_ui(new Ui::EmulatorTabWidget())
{
    m_ui->setupUi(this);
}

EmulatorTabWidget::~EmulatorTabWidget()
{
    delete m_ui;
}
