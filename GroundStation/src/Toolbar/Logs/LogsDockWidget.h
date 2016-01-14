//=============================================================================================
//
// Filename   : LogsDockWidget.h
// Author     : Kuba Sejdak
// Created on : 08.02.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//=============================================================================================

#ifndef LOGSDOCKWIDGET_H
#define LOGSDOCKWIDGET_H

#include <QDockWidget>

namespace Ui {
    class LogsDockWidget;
}

class LogsDockWidget : public QDockWidget {
    Q_OBJECT

public:
    explicit LogsDockWidget(QWidget* parent = 0);
    ~LogsDockWidget();

public slots:
    void showLoggingOptions();
    void init();

private:
    Ui::LogsDockWidget* m_ui;
};

#endif
