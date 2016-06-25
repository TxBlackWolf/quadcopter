////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       05.02.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef TCPOPTIONS_H
#define TCPOPTIONS_H

#include <QSettings>
#include <QString>

#include <stdint.h>

class TCPOptions {
public:
    void save(QSettings& settings);
    void load(QSettings& settings);

public:
    QString address;
    uint16_t port;
};

#endif
