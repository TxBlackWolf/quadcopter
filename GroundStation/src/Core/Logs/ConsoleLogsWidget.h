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

#include <QFile>
#include <QMutex>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTextStream>
#include <QWidget>

namespace Ui {
    class ConsoleLogsWidget;
}

class ConsoleLogsWidget : public QWidget {
    Q_OBJECT

public:
    explicit ConsoleLogsWidget(QWidget* parent = 0);
    virtual ~ConsoleLogsWidget();

public slots:
    void startNetworkServer();
    void stopNetworkServer();
    void accept();
    void readSocket();
    void clientDisconnected();

private:
    Ui::ConsoleLogsWidget* m_ui;

    QTcpServer m_tcpServer;
    QTcpSocket* m_socket;
    QMutex m_mutex;
    QFile m_logFile;
    QTextStream m_logStream;
};

#endif
