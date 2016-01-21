////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       09.02.2015
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

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
