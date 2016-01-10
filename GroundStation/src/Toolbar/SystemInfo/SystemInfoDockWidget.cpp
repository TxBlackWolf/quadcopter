//============================================================================
//
// Filename   : SystemInfoDockWidget.cpp
// Author     : Kuba Sejdak
// Created on : 11 lut 2015
//
//============================================================================

#include "SystemInfoDockWidget.h"
#include "ui_SystemInfoDockWidget.h"

SystemInfoDockWidget::SystemInfoDockWidget(QWidget* parent)
    : QDockWidget(parent)
    , m_ui(new Ui::SystemInfoDockWidget)
{
    m_ui->setupUi(this);
}

SystemInfoDockWidget::~SystemInfoDockWidget()
{
    delete m_ui;
}
