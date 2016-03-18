////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       01.12.2014
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef LOGSOPTIONS_H
#define LOGSOPTIONS_H

#include "ServerOptions.h"

#include <QString>

class LogsOptions {
public:
    void save();
    void load();

public:
    bool serialLogsEnabled;
    QString logsPath;

    ServerOptions serverOptions;
};

#endif
