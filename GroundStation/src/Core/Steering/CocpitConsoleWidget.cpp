#include "CocpitConsoleWidget.h"
#include "ui_CocpitConsoleWidget.h"

CocpitConsoleWidget::CocpitConsoleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CocpitConsoleWidget)
{
    ui->setupUi(this);
}

CocpitConsoleWidget::~CocpitConsoleWidget()
{
    delete ui;
}
