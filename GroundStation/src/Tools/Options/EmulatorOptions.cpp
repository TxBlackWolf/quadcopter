////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       08.02.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "EmulatorOptions.h"

#include <QSettings>

void EmulatorOptions::save()
{
    QSettings settings;

    settings.beginGroup("EmulatorOptions");
    settings.beginGroup("NetworkLogs");
    emulatorServer.save(settings);
    settings.endGroup();
    settings.endGroup();
}

void EmulatorOptions::load()
{
    QSettings settings;

    settings.beginGroup("EmulatorOptions");
    settings.beginGroup("NetworkLogs");
    emulatorServer.load(settings);
    settings.endGroup();
    settings.endGroup();
}
