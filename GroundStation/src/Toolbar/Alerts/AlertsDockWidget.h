//============================================================================
//
// Filename   : AlertsDockWidget.h
// Author     : Kuba Sejdak
// Created on : 11 lut 2015
//
//============================================================================

#ifndef ALERTSDOCKWIDGET_H
#define ALERTSDOCKWIDGET_H

#include <QDockWidget>

namespace Ui
{
    class AlertsDockWidget;
}

class AlertsDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit AlertsDockWidget(QWidget* parent = 0);
    ~AlertsDockWidget();

private:
    Ui::AlertsDockWidget* m_ui;
};

#endif
