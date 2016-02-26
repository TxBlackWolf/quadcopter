////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       07.02.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "SystemInfoWidget.h"
#include "ui_SystemInfoWidget.h"

SystemInfoWidget::SystemInfoWidget(QWidget* parent)
    : QWidget(parent)
    , m_ui(new Ui::SystemInfoWidget)
{
    m_ui->setupUi(this);
}

SystemInfoWidget::~SystemInfoWidget()
{
    delete m_ui;
}
