////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       14.01.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

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
