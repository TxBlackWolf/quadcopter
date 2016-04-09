////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       08.02.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef COMMANDSOPTIONS_H
#define COMMANDSOPTIONS_H

#include "Common/ServerOptions.h"

#include <QString>

class CommandsOptions {
public:
    void save();
    void load();

public:
    ServerOptions serverOptions;
};

#endif
