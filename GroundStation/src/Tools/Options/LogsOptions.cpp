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
    settings.setValue("serialLogsEnabled", serialLogsEnabled);
    settings.setValue("logsPath", logsPath);
    settings.beginGroup("SerialLogs");
    serialLogs.save(settings);
    settings.endGroup();
    settings.beginGroup("NetworkLogs");
    networkLogs.save(settings);
    settings.endGroup();
    settings.endGroup();
}

void LogsOptions::load()
{
    QSettings settings;

    settings.beginGroup("LogsOptions");
    serialLogsEnabled = settings.value("serialLogsEnabled", true).toBool();
    logsPath = settings.value("logsPath", QDir::currentPath()).toString();
    settings.beginGroup("SerialLogs");
    serialLogs.load(settings);
    settings.endGroup();
    settings.beginGroup("NetworkLogs");
    networkLogs.load(settings);
    settings.endGroup();
    settings.endGroup();
}
