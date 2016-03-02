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
		disconnect(m_socket, SIGNAL(readyRead()), this, SLOT(receiveSpecificData()));
		disconnect(m_socket, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
		m_socket->close();
		m_socket = nullptr;
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

	if(m_options.singleClient)
		m_tcpServer.close();

	if(m_onClientConnectedCallback) {
		/// @todo Add string with client ip:port.
		m_onClientDisconnectedCallback("<unknown>");
	}
}

void TCPServer::clientDisconnected()
{
	disconnect(m_socket, SIGNAL(readyRead()), this, SLOT(readSocket()));
	disconnect(m_socket, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
	m_socket = nullptr;

	m_tcpServer.listen(QHostAddress::Any, m_options.port);

	if(m_onClientDisconnectedCallback) {
		/// @todo Add string with client ip:port.
		m_onClientDisconnectedCallback("<unknown>");
	}
}
