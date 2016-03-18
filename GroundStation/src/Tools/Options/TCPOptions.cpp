////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       05.02.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "TCPOptions.h"

void TCPOptions::save(QSettings& settings)
{
    settings.beginGroup("TCPOptions");
    settings.setValue("address", address);
    settings.setValue("port", port);
    settings.setValue("singleClient", singleClient);
    settings.endGroup();
}

void TCPOptions::load(QSettings& settings)
{
    settings.beginGroup("TCPOptions");
    address = settings.value("address", "127.0.0.1").toString();
    port = settings.value("port", 12555).toUInt();
    singleClient = settings.value("singleClient", true).toBool();
    settings.endGroup();
}
