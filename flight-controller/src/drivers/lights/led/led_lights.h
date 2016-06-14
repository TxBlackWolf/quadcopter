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

typedef struct {
    GPIOHandle_t gpio;
    uint8_t phase;
	bool state;
	bool initialized;
} StrobeLight_t;

#endif
