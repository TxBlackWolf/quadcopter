////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       15.09.2015
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef ENGINE_H
#define ENGINE_H

#include "hal/pwm.h"

#include <stdbool.h>

typedef enum {
    ENGINE_FRONT_LEFT,
    ENGINE_FRONT_RIGHT,
    ENGINE_REAR_LEFT,
    ENGINE_REAR_RIGHT,
    ENGINE_COUNT
} EngineId_t;

bool engines_init();

void engines_enableOne(EngineId_t engine);
void engines_disableOne(EngineId_t engine);
void engines_enableAll();
void engines_disableAll();

void engines_setThrottle(EngineId_t engine, uint32_t throttle_perc);

#endif
