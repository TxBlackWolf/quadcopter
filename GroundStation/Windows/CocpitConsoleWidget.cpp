////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       06.02.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "CocpitConsoleWidget.h"
#include "ui_CocpitConsoleWidget.h"

CocpitConsoleWidget::CocpitConsoleWidget(QWidget* parent)
    : QWidget(parent)
    , m_ui(new Ui::CocpitConsoleWidget())
{
    m_ui->setupUi(this);
}

CocpitConsoleWidget::~CocpitConsoleWidget()
{
    delete m_ui;
}
