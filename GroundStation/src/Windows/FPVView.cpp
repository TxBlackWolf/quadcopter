////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       21.02.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "FPVView.h"
#include "ui_FPVView.h"

FPVView::FPVView(QWidget* parent)
    : QWidget(parent)
    , m_ui(new Ui::FPVView())
{
    m_ui->setupUi(this);
}

FPVView::~FPVView()
{
    delete m_ui;
}
