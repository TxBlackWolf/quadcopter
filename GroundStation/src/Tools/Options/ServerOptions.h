////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       02.03.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef SERVEROPTIONS_H
#define SERVEROPTIONS_H

#include "SerialPortOptions.h"
#include "TCPOptions.h"

#include <QSettings>

class ServerOptions {
public:
    typedef enum {
        SERVER_TCP,
        SERVER_SERIAL
    } ServerType;

    void save(QSettings& settings);
    void load(QSettings& settings);

public:
    ServerType serverType;
    SerialPortOptions serialServer;
    TCPOptions tcpServer;
};

#endif
