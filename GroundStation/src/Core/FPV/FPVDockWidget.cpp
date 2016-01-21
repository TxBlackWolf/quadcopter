////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       11.02.2015
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "FPVDockWidget.h"
#include "ui_FPVDockWidget.h"

FPVDockWidget::FPVDockWidget(QWidget* parent)
    : QDockWidget(parent)
    , m_ui(new Ui::FPVDockWidget())
{
    m_ui->setupUi(this);
}

FPVDockWidget::~FPVDockWidget()
{
    delete m_ui;
}
