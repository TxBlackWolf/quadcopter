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
#include <QDebug>
#include <QDir>
#include <QMutexLocker>

ConsoleLogsWidget::ConsoleLogsWidget(QWidget* parent)
    : QWidget(parent)
    , m_ui(new Ui::ConsoleLogsWidget())
    , m_socket(nullptr)
    , m_logStream(&m_logFile)
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
    disconnect(m_ui->buttonStart, SIGNAL(clicked()), this, SLOT(stopNetworkServer()));
    connect(m_ui->buttonStart, SIGNAL(clicked()), this, SLOT(startNetworkServer()));
    m_ui->buttonStart->setText("Start");

    if(m_socket) {
        disconnect(m_socket, SIGNAL(readyRead()), this, SLOT(readSocket()));
        disconnect(m_socket, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
        m_socket->close();
        m_socket = nullptr;
        m_logFile.close();
    }

    if(m_tcpServer.isListening())
        m_tcpServer.close();
}

void ConsoleLogsWidget::accept()
{
    m_socket = m_tcpServer.nextPendingConnection();
    if(!m_socket)
        return;

    connect(m_socket, SIGNAL(readyRead()), this, SLOT(readSocket()));
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));

    // We accept only one client.
    m_tcpServer.close();

    LogsOptions options;
    options.load();

    QDir().mkpath(options.logsPath);
    QString logFileName = QString("%1/GroundStation_%2.log").arg(options.logsPath).arg(QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss"));
    m_logFile.setFileName(logFileName);
    m_logFile.open(QFile::Append | QFile::Text);
}

void ConsoleLogsWidget::readSocket()
{
    QTcpSocket* socket = dynamic_cast<QTcpSocket*>(sender());
    QString message = socket->readAll();
    QString currentTimestamp = QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm");
    message = "[" + currentTimestamp + "] " + message;

    QMutexLocker locker(&m_mutex);
    m_ui->textEditLogs->insertPlainText(message);
    m_logStream << message;
    m_logStream.flush();
}

void ConsoleLogsWidget::clientDisconnected()
{
    disconnect(m_socket, SIGNAL(readyRead()), this, SLOT(readSocket()));
    disconnect(m_socket, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
    m_socket = nullptr;

    LogsOptions options;
    options.load();
    m_tcpServer.listen(QHostAddress::Any, options.networkLogs.port);

    m_logFile.close();
}
