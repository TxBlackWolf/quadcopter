////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       12.08.2015
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef LED_LIGHTS_H
#define LED_LIGHTS_H

#include "drivers/lights/lights.h"
#include "hal/gpio.h"

#include <stdint.h>

/// @brief LED strobe meta data.
typedef struct {
    GPIOHandle_t gpio;          ///< GPIO handle for strobe pin.
    uint8_t phase;              ///< Current strobe phase in blinking action.
    bool state;                 ///< Flag indicating if strobe is currently on or off.
    bool initialized;           ///< Flag indicating if strobe LED is initialized.
} LEDStrobe_t;

#endif
