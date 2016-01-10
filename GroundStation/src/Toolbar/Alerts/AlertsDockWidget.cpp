//============================================================================
//
// Filename   : AlertsDockWidget.cpp
// Author     : Kuba Sejdak
// Created on : 11 lut 2015
//
//============================================================================

#include "AlertsDockWidget.h"
#include "ui_AlertsDockWidget.h"

AlertsDockWidget::AlertsDockWidget(QWidget* parent)
    : QDockWidget(parent)
    , m_ui(new Ui::AlertsDockWidget)
{
    m_ui->setupUi(this);
}

AlertsDockWidget::~AlertsDockWidget()
{
    delete m_ui;
}
