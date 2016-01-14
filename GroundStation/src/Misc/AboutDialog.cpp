//---------------------------------------------------------------------------------------------------------------
//
// Filename   : AboutDialog.cpp
// Author     : Kuba Sejdak
// Created on : 29.11.2014
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#include "AboutDialog.h"
#include "ui_AboutDialog.h"

AboutDialog::AboutDialog(QWidget* parent)
    : QDialog(parent)
    , m_ui(new Ui::AboutDialog())
{
    m_ui->setupUi(this);
}

AboutDialog::~AboutDialog()
{
    delete m_ui;
}
