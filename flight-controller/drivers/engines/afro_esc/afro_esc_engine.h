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

#define GET_ENGINE_PORT(id)             id##_PORT               ///< Macro creating engine port symbol.
#define GET_ENGINE_PIN(id)              id##_PIN                ///< Macro creating engine pin symbol.
#define GET_ENGINE_NAME(id)             #id                     ///< Macro creating engine name string.
#define GET_ENGINE_TIMER(id)            id##_TIMER              ///< Macro creating engine timer symbol.
#define GET_ENGINE_TIMER_CHANNEL(id)    id##_TIMER_CHANNEL      ///< Macro creating engine timer channel symbol.

/// @brief Engine meta data.
typedef struct {
    PWMHandle_t handle;             ///< PWM handle for controlling engine.
    bool initialized;               ///< Flag indicating if engine in initialized.
} Engine_t;

#endif
