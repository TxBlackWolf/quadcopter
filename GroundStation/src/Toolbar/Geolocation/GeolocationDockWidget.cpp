//============================================================================
//
// Filename   : GeolocationDockWidget.cpp
// Author     : Kuba Sejdak
// Created on : 09 lut 2015
//
//============================================================================

#include "GeolocationDockWidget.h"
#include "ui_GeolocationDockWidget.h"

GeolocationDockWidget::GeolocationDockWidget(QWidget* parent)
    : QDockWidget(parent)
    , m_ui(new Ui::GeolocationDockWidget)
{
    m_ui->setupUi(this);
}

GeolocationDockWidget::~GeolocationDockWidget()
{
    delete m_ui;
}
