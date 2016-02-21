////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       21.02.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef ALERTSWIDGET_H
#define ALERTSWIDGET_H

#include <QWidget>

namespace Ui {
    class AlertsWidget;
}

class AlertsWidget : public QWidget {
    Q_OBJECT

public:
    explicit AlertsWidget(QWidget* parent = nullptr);
    virtual ~AlertsWidget();

private:
    Ui::AlertsWidget* m_ui;
};

#endif
