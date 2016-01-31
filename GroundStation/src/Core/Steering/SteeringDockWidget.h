////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       11.02.2015
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef STEERINGWIDGET_H
#define STEERINGWIDGET_H

#include <QDockWidget>

namespace Ui {
    class SteeringDockWidget;
}

class SteeringDockWidget : public QDockWidget {
    Q_OBJECT

public:
    explicit SteeringDockWidget(QWidget* parent = 0);
    virtual ~SteeringDockWidget();

private:
    Ui::SteeringDockWidget* m_ui;
};

#endif
