////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       15.09.2015
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef AFRO_ESC_ENGINE_H
#define AFRO_ESC_ENGINE_H

#include <stdbool.h>

#include "drivers/engines/engine.h"

#define GET_ENGINE_PORT(id)             id##_PORT
#define GET_ENGINE_PIN(id)              id##_PIN
#define GET_ENGINE_NAME(id)             #id
#define GET_ENGINE_TIMER(id)            id##_TIMER
#define GET_ENGINE_TIMER_CHANNEL(id)    id##_TIMER_CHANNEL

typedef struct {
    PWMHandle_t handle;
    bool initialized;
} Engine_t;

#endif
