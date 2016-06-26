////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       12.08.2015
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "led_lights.h"
#include "board/board.h"
#include "board/clock.h"
#include "board/console.h"
#include "hal/timer.h"

#define STROBE_DELAY_PERIOD_MSEC    2000        ///< Delay between strobe blinking actions.
#define STROBE_BLINK_PERIOD_MSEC    150         ///< Delay between strobe on/off states when blinking.

static LEDStrobe_t strobe;

//=============================================================================================
// HELPER FUNCTIONS
//=============================================================================================

/// @brief Callback, that switches LED strobe states and sets delay for next action.
static void strobe_blink()
{
    uint32_t period_ms = 0;

    switch (strobe.phase) {
    case 1:
        gpio_writePin(&strobe.gpio, true);
        period_ms = STROBE_BLINK_PERIOD_MSEC;
        strobe.phase = 2;
        break;
    case 2:
        gpio_writePin(&strobe.gpio, false);
        period_ms = STROBE_BLINK_PERIOD_MSEC;
        strobe.phase = 3;
        break;
    case 3:
        gpio_writePin(&strobe.gpio, true);
        period_ms = STROBE_BLINK_PERIOD_MSEC;
        strobe.phase = 4;
        break;
    case 4:
        gpio_writePin(&strobe.gpio, false);
        period_ms = STROBE_DELAY_PERIOD_MSEC;
        strobe.phase = 1;
        break;
    }

     clock_addPeriodicCallbackAsync(strobe_blink, period_ms, 1);
}

//=============================================================================================
// INTERFACE FUNCTIONS
//=============================================================================================

bool strobe_init()
{
    strobe.state = false;
    strobe.phase = 1;

    GPIOConfig_t gpio_config;
    gpio_config.direction = GPIO_DIRECTION_OUT;
    gpio_config.resistor_type = GPIO_RESISTOR_NONE;

    if (!board_strobeInit(&strobe.gpio, &gpio_config))
        return false;

    console_write("lights: Initialized %s (GPIO P%d.%d)\n", strobe.gpio.name, strobe.gpio.port, strobe.gpio.pin);
    strobe.initialized = true;
    return true;
}

void strobe_enable()
{
    if (!strobe.initialized)
        return;

    gpio_activate(&strobe.gpio);
    clock_addPeriodicCallback(strobe_blink, STROBE_DELAY_PERIOD_MSEC, 1);
}

void strobe_disable()
{
    if (!strobe.initialized)
        return;

    gpio_deactivate(&strobe.gpio);
    clock_removePeriodicCallback(strobe_blink);
}
