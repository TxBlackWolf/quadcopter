////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       01.12.2014
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "LogsOptions.h"

#include <QDir>
#include <QSettings>

void LogsOptions::save()
{
    QSettings settings;

    settings.beginGroup("LogsOptions");
    settings.setValue("logsPath", logsPath);
    serverOptions.save(settings);
    settings.endGroup();
}

void LogsOptions::load()
{
    QSettings settings;

    settings.beginGroup("LogsOptions");
    logsPath = settings.value("logsPath", QDir::currentPath()).toString();
    serverOptions.load(settings);
    settings.endGroup();
}
