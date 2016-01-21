////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       11.02.2015
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "TelemetryDockWidget.h"
#include "ui_TelemetryDockWidget.h"

TelemetryDockWidget::TelemetryDockWidget(QWidget* parent)
    : QDockWidget(parent)
    , m_ui(new Ui::TelemetryDockWidget)
{
    m_ui->setupUi(this);
}

TelemetryDockWidget::~TelemetryDockWidget()
{
    delete m_ui;
}
