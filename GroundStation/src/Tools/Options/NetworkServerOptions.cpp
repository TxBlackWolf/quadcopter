////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       05.02.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "NetworkServerOptions.h"

void NetworkServerOptions::save(QSettings& settings)
{
    settings.beginGroup("NetworkServerOptions");
    settings.setValue("address", address);
    settings.setValue("port", port);
    settings.endGroup();
}

void NetworkServerOptions::load(QSettings& settings, QString defaultAddress, uint16_t defaultPort)
{
    settings.beginGroup("NetworkServerOptions");
    address = settings.value("address", defaultAddress).toString();
    port = settings.value("port", defaultPort).toUInt();
    settings.endGroup();
}
