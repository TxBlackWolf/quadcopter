////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       23.03.2015
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "TelemetryTabWidget.h"
#include "ui_TelemetryTabWidget.h"

TelemetryTabWidget::TelemetryTabWidget(QWidget* parent)
    : QTabWidget(parent)
    , m_ui(new Ui::TelemetryTabWidget)
{
    m_ui->setupUi(this);

    connect(m_ui->buttonClear, SIGNAL(clicked()), this, SLOT(onClearButtonClicked()));
}

TelemetryTabWidget::~TelemetryTabWidget()
{
    clear();
    delete m_ui;
}

void TelemetryTabWidget::clear()
{
    qDeleteAll(m_treeItems);
    m_treeItems.clear();
}

void TelemetryTabWidget::onClearButtonClicked()
{
    clear();
}
