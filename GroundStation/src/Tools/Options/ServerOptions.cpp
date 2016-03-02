////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       02.03.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "ServerOptions.h"

void ServerOptions::save(QSettings& settings)
{
	settings.beginGroup("ServerOptions");
	settings.setValue("serverType", serverType);
	serialServer.save(settings);
	tcpServer.save(settings);
	settings.endGroup();
}

void ServerOptions::load(QSettings& settings)
{
	settings.beginGroup("ServerOptions");
	serverType = static_cast<ServerType>(settings.value("serverType", SERVER_TCP).toInt());
	serialServer.load(settings);
	tcpServer.load(settings);
	settings.endGroup();
}
