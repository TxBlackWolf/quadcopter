////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       21.01.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "GoogleMapsView.h"
#include "ui_GoogleMapsView.h"

GoogleMapsView::GoogleMapsView(QWidget* parent)
    : QWidget(parent)
    , m_ui(new Ui::GoogleMapsView())
{
    m_ui->setupUi(this);
}

GoogleMapsView::~GoogleMapsView()
{
    delete m_ui;
}
