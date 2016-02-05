////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       05.02.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef NETWORKSERVEROPTIONS_H
#define NETWORKSERVEROPTIONS_H

#include <QSettings>
#include <QString>

class NetworkServerOptions {
public:
    void save(QSettings& settings);
    void load(QSettings& settings);

public:
    QString address;
    unsigned int port;
};

#endif
