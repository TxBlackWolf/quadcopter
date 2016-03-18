////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       08.02.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef EMULATOROPTIONS_H
#define EMULATOROPTIONS_H

#include "TCPOptions.h"

#include <QString>

class EmulatorOptions {
public:
    void save();
    void load();

public:
    TCPOptions emulatorServer;
};

#endif
