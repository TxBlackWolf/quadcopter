////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       21.02.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "AlertsWidget.h"
#include "ui_AlertsWidget.h"

AlertsWidget::AlertsWidget(QWidget* parent)
    : QWidget(parent)
    , m_ui(new Ui::AlertsWidget())
{
    m_ui->setupUi(this);
}

AlertsWidget::~AlertsWidget()
{
    delete m_ui;
}
