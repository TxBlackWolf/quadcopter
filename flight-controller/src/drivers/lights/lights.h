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

bool strobe_init();
void strobe_enable();
void strobe_disable();

void strobe_blink();

#endif
