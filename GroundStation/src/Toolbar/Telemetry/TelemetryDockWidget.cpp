//============================================================================
//
// Filename   : TelemetryDockWidget.cpp
// Author     : Kuba Sejdak
// Created on : 11 lut 2015
//
//============================================================================

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
