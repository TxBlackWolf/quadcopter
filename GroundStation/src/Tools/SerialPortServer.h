////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       19.03.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef SERIALPORTSERVER_H
#define SERIALPORTSERVER_H

#include "IServer.h"
#include "Options/SerialPortOptions.h"

#include <QSerialPort>

class SerialPortServer : public IServer {
public:
    SerialPortServer();

    virtual bool start(ServerOptions options);
    virtual void stop();

private:
    void init();
    virtual void acceptConnection() {}
    virtual bool receiveDataPriv();
    virtual void clientDisconnected() {}
    QString getClientName();

private:
    QSerialPort m_serialPort;
    SerialPortOptions m_options;
    bool m_firstIncomingData;
};

#endif
