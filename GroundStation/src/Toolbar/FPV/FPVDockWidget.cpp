//============================================================================
//
// Filename   : FPVDockWidget.cpp
// Author     : Kuba Sejdak
// Created on : 11 lut 2015
//
//============================================================================

#include "FPVDockWidget.h"
#include "ui_FPVDockWidget.h"

FPVDockWidget::FPVDockWidget(QWidget* parent)
    : QDockWidget(parent)
    , m_ui(new Ui::FPVDockWidget)
{
    m_ui->setupUi(this);
}

FPVDockWidget::~FPVDockWidget()
{
    delete m_ui;
}
