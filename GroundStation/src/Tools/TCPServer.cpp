////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       26.02.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "TCPServer.h"

TCPServer::TCPServer()
    : m_socket(nullptr)
{
}

bool TCPServer::start()
{
    /// @todo Implement.
    return false;
}

void TCPServer::stop()
{
    if(m_socket) {
        disconnect(m_socket, SIGNAL(readyRead()), this, SLOT(receiveSpecificData()));
        disconnect(m_socket, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
        m_socket->close();
        m_socket = nullptr;
        m_logFile.close();
    }

    if(m_tcpServer.isListening())
        m_tcpServer.close();
}

bool TCPServer::receiveSpecificData()
{
    QTcpSocket* socket = dynamic_cast<QTcpSocket*>(sender());
    m_data = socket->readAll();

    return true;
}

void TCPServer::init()
{
    connect(&m_tcpServer, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
}

void TCPServer::acceptConnection()
{
    m_socket = m_tcpServer.nextPendingConnection();
    if(!m_socket)
        return;

    connect(m_socket, SIGNAL(readyRead()), this, SLOT(readSocket()));
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));

    // We accept only one client.
    /// @todo Check if accept only one client.
    m_tcpServer.close();
}

void TCPServer::clientDisconnected()
{
    disconnect(m_socket, SIGNAL(readyRead()), this, SLOT(readSocket()));
    disconnect(m_socket, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
    m_socket = nullptr;

    LogsOptions options;
    options.load();
    m_tcpServer.listen(QHostAddress::Any, options.networkLogs.port);
}
