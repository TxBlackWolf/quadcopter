//---------------------------------------------------------------------------------------------------------------
//
// Filename   : ConsoleLogsWidget.h
// Author     : Kuba Sejdak
// Created on : 14.01.2016
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#ifndef CONSOLELOGSWIDGET_H
#define CONSOLELOGSWIDGET_H

#include <QWidget>

namespace Ui {
    class ConsoleLogsWidget;
}

class ConsoleLogsWidget : public QWidget {
    Q_OBJECT

public:
    explicit ConsoleLogsWidget(QWidget* parent = 0);
    ~ConsoleLogsWidget();

private:
    Ui::ConsoleLogsWidget* m_ui;
};

#endif
