////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       14.01.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "ConsoleLogsWidget.h"
#include "ui_ConsoleLogsWidget.h"

#include "Tools/Options/LogsOptions.h"

#include <QDateTime>
#include <QMutexLocker>

ConsoleLogsWidget::ConsoleLogsWidget(QWidget* parent)
    : QWidget(parent)
    , m_ui(new Ui::ConsoleLogsWidget())
{
    m_ui->setupUi(this);

    connect(m_ui->buttonStart, SIGNAL(clicked()), this, SLOT(startNetworkServer()));
    connect(m_ui->buttonClear, SIGNAL(clicked()), m_ui->textEditLogs, SLOT(clear()));
    connect(&m_tcpServer, SIGNAL(newConnection()), this, SLOT(accept()));
}

ConsoleLogsWidget::~ConsoleLogsWidget()
{
    delete m_ui;
}

void ConsoleLogsWidget::startNetworkServer()
{
    LogsOptions options;
    options.load();

    // This is non-blocking call.
    if(!m_tcpServer.listen(QHostAddress::Any, options.networkLogs.port))
        return;

    disconnect(m_ui->buttonStart, SIGNAL(clicked()), this, SLOT(startNetworkServer()));
    connect(m_ui->buttonStart, SIGNAL(clicked()), this, SLOT(stopNetworkServer()));
    m_ui->buttonStart->setText("Stop");
}

void ConsoleLogsWidget::stopNetworkServer()
{
    if(!m_tcpServer.isListening())
        return;

    m_tcpServer.close();

    disconnect(m_ui->buttonStart, SIGNAL(clicked()), this, SLOT(stopNetworkServer()));
    connect(m_ui->buttonStart, SIGNAL(clicked()), this, SLOT(startNetworkServer()));
    m_ui->buttonStart->setText("Start");
}

void ConsoleLogsWidget::accept()
{
    QTcpSocket* socket = m_tcpServer.nextPendingConnection();
    if(!socket)
        return;

    connect(socket, SIGNAL(readyRead()), this, SLOT(readSocket()));
}

void ConsoleLogsWidget::readSocket()
{
    QTcpSocket* socket = dynamic_cast<QTcpSocket*>(sender());
    QString message = socket->readAll();
    message += "\n";

    QString currentTimestamp = QDateTime::currentDateTime().toString();
    message = "[" + currentTimestamp + "] " + message;

    QMutexLocker locker(&m_mutex);
    m_ui->textEditLogs->insertPlainText(message);
}
