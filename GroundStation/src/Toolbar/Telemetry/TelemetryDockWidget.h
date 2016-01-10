//============================================================================
//
// Filename   : TelemetryDockWidget.h
// Author     : Kuba Sejdak
// Created on : 11 lut 2015
//
//============================================================================

#ifndef TELEMETRYDOCKWIDGET_H
#define TELEMETRYDOCKWIDGET_H

#include <QDockWidget>

namespace Ui
{
    class TelemetryDockWidget;
}

class TelemetryDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit TelemetryDockWidget(QWidget* parent = 0);
    ~TelemetryDockWidget();

private:
    Ui::TelemetryDockWidget* m_ui;
};

#endif
