//=============================================================================================
//
// Filename   : AlertsDockWidget.h
// Author     : Kuba Sejdak
// Created on : 11.02.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//=============================================================================================

#ifndef ALERTSDOCKWIDGET_H
#define ALERTSDOCKWIDGET_H

#include <QDockWidget>

namespace Ui {
    class AlertsDockWidget;
}

class AlertsDockWidget : public QDockWidget {
    Q_OBJECT

public:
    explicit AlertsDockWidget(QWidget* parent = 0);
    ~AlertsDockWidget();

private:
    Ui::AlertsDockWidget* m_ui;
};

#endif
