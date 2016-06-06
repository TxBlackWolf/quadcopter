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

void TCPServer::sendData(const QByteArray& buffer)
{
    if(m_socket)
        m_socket->write(buffer);
}

bool TCPServer::receiveDataPriv()
{
    QTcpSocket* socket = dynamic_cast<QTcpSocket*>(sender());
    m_data = socket->readAll();
    return (m_data.size() > 0);
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

    connect(m_socket, SIGNAL(readyRead()), this, SLOT(receiveData()));
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));

    m_tcpServer.close();

    if(m_onClientConnectedCallback)
        m_onClientConnectedCallback(getClientName());
}

void TCPServer::clientDisconnected()
{
    disconnect(m_socket, SIGNAL(readyRead()), this, SLOT(receiveData()));
    disconnect(m_socket, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));

    m_tcpServer.listen(QHostAddress::Any, m_options.port);

    if(m_onClientDisconnectedCallback)
        m_onClientDisconnectedCallback(getClientName());

    m_socket = nullptr;
}

QString TCPServer::getClientName()
{
    return QString("%1:%2").arg(m_socket->peerAddress().toString()).arg(m_socket->peerPort());
}
