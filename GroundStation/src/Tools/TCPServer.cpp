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
#include "Options/TCPOptions.h"

TCPServer::TCPServer()
    : m_socket(nullptr)
{
    init();
}

bool TCPServer::start(ServerOptions options)
{
    m_options = options.tcpServer;

    // This is non-blocking call.
    return m_tcpServer.listen(QHostAddress::Any, m_options.port);
}

void TCPServer::stop()
{
    if(m_socket) {
        disconnect(m_socket, SIGNAL(readyRead()), this, SLOT(receiveData()));
        disconnect(m_socket, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
        m_socket->close();
        m_socket = nullptr;
    }

    if(m_tcpServer.isListening())
        m_tcpServer.close();
}

bool TCPServer::receiveDataPriv()
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
    /// @todo Add support for list of sockets.
    m_socket = m_tcpServer.nextPendingConnection();
    if(!m_socket)
        return;

    connect(m_socket, SIGNAL(readyRead()), this, SLOT(receiveData()));
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));

    if(m_options.singleClient)
        m_tcpServer.close();

    if(m_onClientConnectedCallback) {
        QString clientName = QString("%1:%2").arg(m_socket->peerAddress().toString()).arg(m_socket->peerPort());
        m_onClientConnectedCallback(clientName);
    }
}

void TCPServer::clientDisconnected()
{
    disconnect(m_socket, SIGNAL(readyRead()), this, SLOT(receiveData()));
    disconnect(m_socket, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));

    m_tcpServer.listen(QHostAddress::Any, m_options.port);

    if(m_onClientDisconnectedCallback) {
        QString clientName = QString("%1:%2").arg(m_socket->peerAddress().toString()).arg(m_socket->peerPort());
        m_onClientDisconnectedCallback(clientName);
    }

    m_socket = nullptr;
}
