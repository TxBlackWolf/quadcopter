////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       14.01.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CONSOLELOGSWIDGET_H
#define CONSOLELOGSWIDGET_H

#include <QMutex>
#include <QTcpServer>
#include <QTcpSocket>
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

    QTcpServer m_tcpServer;
    QMutex m_mutex;
};

#endif
