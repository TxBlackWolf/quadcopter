//=============================================================================================
//
// Filename   : ConsoleLogsWidget.cpp
// Author     : Kuba Sejdak
// Created on : 14.01.2016
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//=============================================================================================

#include "ConsoleLogsWidget.h"
#include "ui_ConsoleLogsWidget.h"

ConsoleLogsWidget::ConsoleLogsWidget(QWidget *parent)
    : QWidget(parent)
    , m_ui(new Ui::ConsoleLogsWidget())
{
    m_ui->setupUi(this);
}

ConsoleLogsWidget::~ConsoleLogsWidget()
{
    delete m_ui;
}
