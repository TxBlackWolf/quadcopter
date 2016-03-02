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

std::unique_ptr<IServer> IServer::create()
{
    return std::unique_ptr<IServer>(new TCPServer());
}

void IServer::setMessageCallback(std::function<void(const QByteArray&)> onMessageCallback)
{
    m_onMessageCallback = onMessageCallback;
}

void IServer::receiveData()
{
    if(receiveSpecificData())
        m_onMessageCallback(m_data);
}
