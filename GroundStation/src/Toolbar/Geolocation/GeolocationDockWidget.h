//============================================================================
//
// Filename   : GeolocationDockWidget.h
// Author     : Kuba Sejdak
// Created on : 09 lut 2015
//
//============================================================================

#ifndef GEOLOCATIONDOCKWIDGET_H
#define GEOLOCATIONDOCKWIDGET_H

#include <QDockWidget>

namespace Ui
{
    class GeolocationDockWidget;
}

class GeolocationDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit GeolocationDockWidget(QWidget* parent = 0);
    ~GeolocationDockWidget();

private:
    Ui::GeolocationDockWidget* m_ui;
};

#endif
