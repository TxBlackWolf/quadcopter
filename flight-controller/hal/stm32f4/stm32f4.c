////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       11.08.2015
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "stm32f4.h"

#include <stdio.h>

//=============================================================================================
// INTERFACE FUNCTIONS
//=============================================================================================

bool stm32f4_addCallback(HALEventCallback_t *callback_set, HALEventCallback_t callback)
{
    for (int i = 0; i < STM32F4_MAX_CALLBACK_COUNT; ++i) {
        if (callback_set[i] != NULL)
            continue;

        callback_set[i] = callback;
        return true;
    }

    return false;
}

bool stm32f4_removeCallback(HALEventCallback_t *callback_set, HALEventCallback_t callback, int *slots_used)
{
    for (int i = 0; i < STM32F4_MAX_CALLBACK_COUNT; ++i) {
        if (callback_set[i] == NULL) {
            (*slots_used)--;
            continue;
        }

        if (callback_set[i] != callback)
            continue;

        callback_set[i] = NULL;
        (*slots_used)--;
        return true;
    }

    return false;
}
