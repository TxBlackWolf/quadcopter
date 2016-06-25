////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       11.08.2015
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef STM32F4_H
#define STM32F4_H

#include "hal/hal.h"

#include <stdbool.h>

#define STM32F4_MAX_CALLBACK_COUNT      5

bool stm32f4_addCallback(HALEventCallback_t *callback_set, HALEventCallback_t callback);
bool stm32f4_removeCallback(HALEventCallback_t *callback_set, HALEventCallback_t callback, int *slots_used);

#endif
