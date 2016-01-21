////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       08.02.2015
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "LogsDockWidget.h"
#include "ui_LogsDockWidget.h"

#include "LogsOptionsDialog.h"

LogsDockWidget::LogsDockWidget(QWidget* parent)
    : QDockWidget(parent)
    , m_ui(new Ui::LogsDockWidget)
{
    m_ui->setupUi(this);
    init();
}

LogsDockWidget::~LogsDockWidget()
{
    delete m_ui;
}

void LogsDockWidget::showLoggingOptions()
{
    LogsOptionsDialog logsOptions;
    logsOptions.exec();
}

void LogsDockWidget::init()
{
    connect(m_ui->buttonOptions, SIGNAL(clicked()), this, SLOT(showLoggingOptions()));
}
