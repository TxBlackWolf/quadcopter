#include "ConsoleLogsWidget.h"
#include "ui_ConsoleLogsWidget.h"

ConsoleLogsWidget::ConsoleLogsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConsoleLogsWidget)
{
    ui->setupUi(this);
}

ConsoleLogsWidget::~ConsoleLogsWidget()
{
    delete ui;
}
