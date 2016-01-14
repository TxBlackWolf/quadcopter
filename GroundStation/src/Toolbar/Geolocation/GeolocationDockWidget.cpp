//=============================================================================================
//
// Filename   : GeolocationDockWidget.cpp
// Author     : Kuba Sejdak
// Created on : 09.02.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//=============================================================================================

#include "GeolocationDockWidget.h"
#include "ui_GeolocationDockWidget.h"

GeolocationDockWidget::GeolocationDockWidget(QWidget* parent)
    : QDockWidget(parent)
    , m_ui(new Ui::GeolocationDockWidget())
{
    m_ui->setupUi(this);
}

GeolocationDockWidget::~GeolocationDockWidget()
{
    delete m_ui;
}
