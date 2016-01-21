////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       09.02.2015
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GEOLOCATIONDOCKWIDGET_H
#define GEOLOCATIONDOCKWIDGET_H

#include <QDockWidget>

namespace Ui {
    class GeolocationDockWidget;
}

class GeolocationDockWidget : public QDockWidget {
    Q_OBJECT

public:
    explicit GeolocationDockWidget(QWidget* parent = 0);
    ~GeolocationDockWidget();

private:
    Ui::GeolocationDockWidget* m_ui;
};

#endif
