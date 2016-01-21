////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       11.02.2015
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "AlertsDockWidget.h"
#include "ui_AlertsDockWidget.h"

AlertsDockWidget::AlertsDockWidget(QWidget* parent)
    : QDockWidget(parent)
    , m_ui(new Ui::AlertsDockWidget())
{
    m_ui->setupUi(this);
}

AlertsDockWidget::~AlertsDockWidget()
{
    delete m_ui;
}
