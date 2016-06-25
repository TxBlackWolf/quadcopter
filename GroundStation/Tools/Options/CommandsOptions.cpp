////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       08.02.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "CommandsOptions.h"

#include <QSettings>

void CommandsOptions::save()
{
    QSettings settings;

    settings.beginGroup("CommandsOptions");
    serverOptions.save(settings);
    settings.endGroup();
}

void CommandsOptions::load()
{
    QSettings settings;

    settings.beginGroup("CommandsOptions");
    serverOptions.load(settings);
    settings.endGroup();
}
