////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       11.02.2015
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "SteeringDockWidget.h"
#include "ui_SteeringDockWidget.h"

SteeringDockWidget::SteeringDockWidget(QWidget* parent)
    : QDockWidget(parent)
    , m_ui(new Ui::SteeringDockWidget())
{
    m_ui->setupUi(this);
}

SteeringDockWidget::~SteeringDockWidget()
{
    delete m_ui;
}
