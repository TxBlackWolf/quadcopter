////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       26.02.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "IServer.h"
#include "Options/Common/TCPOptions.h"

#include <QTcpServer>
#include <QTcpSocket>

class TCPServer : public IServer {
public:
    TCPServer();

    virtual bool start(ServerOptions options);
    virtual void stop();

private:
    void init();
    virtual void acceptConnection();
    virtual bool receiveDataPriv();
    virtual void clientDisconnected();
    QString getClientName();

private:
    QTcpServer m_tcpServer;
    QTcpSocket* m_socket;

    TCPOptions m_options;
};

#endif
