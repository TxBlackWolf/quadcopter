////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       26.02.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "IServer.h"
#include "TCPServer.h"

IServer* IServer::create(ServerOptions::ServerType type)
{
	switch(type) {
    case ServerOptions::SERVER_TCP		: return new TCPServer();
	case ServerOptions::SERVER_SERIAL	: return nullptr;
	}

	return nullptr;
}

void IServer::setOnClientConnectedCallback(std::function<void(const QString&)> onClientConnectedCallback)
{
	m_onClientConnectedCallback = onClientConnectedCallback;
}

void IServer::setOnMessageCallback(std::function<void(const QByteArray&)> onMessageCallback)
{
	m_onMessageCallback = onMessageCallback;
}

void IServer::setOnClientDisconnectedCallback(std::function<void(const QString&)> onClientDisonnectedCallback)
{
	m_onClientDisconnectedCallback = onClientDisonnectedCallback;
}

void IServer::receiveData()
{
    if(!receiveDataPriv())
		return;

	if(m_onMessageCallback)
		m_onMessageCallback(m_data);
}
