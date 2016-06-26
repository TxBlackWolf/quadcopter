////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       12.08.2015
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef LIGHTS_H
#define LIGHTS_H

#include <stdbool.h>

//=============================================================================================
// STROBE LIGHT
//=============================================================================================

/// @brief Initializes strobe light.
/// @note Initializing requires enabling it to start working.
/// @see strobe_enable()
/// @return True on success, false otherwise.
bool strobe_init();

/// @brief Enables strobe light.
void strobe_enable();

/// @brief Disables strobe light.
void strobe_disable();

#endif
