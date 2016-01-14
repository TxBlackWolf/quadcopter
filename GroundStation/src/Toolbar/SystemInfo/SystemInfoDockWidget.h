//---------------------------------------------------------------------------------------------------------------
//
// Filename   : SystemInfoDockWidget.h
// Author     : Kuba Sejdak
// Created on : 11.02.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#ifndef SYSTEMINFODOCKWIDGET_H
#define SYSTEMINFODOCKWIDGET_H

#include <QDockWidget>

namespace Ui {
    class SystemInfoDockWidget;
}

class SystemInfoDockWidget : public QDockWidget {
    Q_OBJECT

public:
    explicit SystemInfoDockWidget(QWidget* parent = 0);
    ~SystemInfoDockWidget();

private:
    Ui::SystemInfoDockWidget* m_ui;
};

#endif
