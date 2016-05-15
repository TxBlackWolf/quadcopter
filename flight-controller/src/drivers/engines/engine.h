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

typedef struct {
    PWMHandle_t front_left;
    PWMHandle_t front_right;
    PWMHandle_t rear_left;
    PWMHandle_t rear_right;
} Engines_t;

bool engines_init();
Engines_t *engines_getHandle();

void engines_enableOne(PWMHandle_t *engine);
void engines_disableOne(PWMHandle_t *engine);
void engines_enableAll();
void engines_disableAll();

void engines_setThrottle(PWMHandle_t *engine, uint32_t throttle_perc);

#endif
