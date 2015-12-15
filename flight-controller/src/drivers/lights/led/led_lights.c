//---------------------------------------------------------------------------------------------------------------
//
// Filename   : led_lights.c
// Author     : Kuba Sejdak
// Created on : 12.08.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#include "led_lights.h"
#include "drivers/lights/lights.h"
#include "hal/gpio.h"
#include "board/board.h"
#include "board/board_pinout.h"
#include "board/clock.h"
#include "board/console.h"

#define STROBE_DELAY_PERIOD_MSEC    2000
#define STROBE_BLINK_PERIOD_MSEC    150

typedef struct {
    GPIOHandle_t gpio;
    bool state;
    uint8_t phase;
} StrobeLight_t;

static StrobeLight_t blue_strobe;

bool strobe_init()
{
    blue_strobe.gpio.port = BLUE_STROBE_PORT;
    blue_strobe.gpio.pin = BLUE_STROBE_PIN;
    blue_strobe.gpio.name = "blue strobe";
    blue_strobe.state = false;
    blue_strobe.phase = 1;

    GPIOConfig_t gpio_config;
    gpio_config.direction = GPIO_DIRECTION_OUT;
    gpio_config.resistor_type = GPIO_RESISTOR_NONE;

    if(!board_strobeInit(&blue_strobe.gpio, gpio_config))
        return false;

    strobe_enable();

    console_write("lights: Initialized %s (GPIO P%d.%d)\n", blue_strobe.gpio.name, blue_strobe.gpio.port, blue_strobe.gpio.pin);
    return true;
}

void strobe_enable()
{
    gpio_activate(&blue_strobe.gpio);
    clock_addPeriodicCallback(strobe_blink, STROBE_DELAY_PERIOD_MSEC, 1);
}

void strobe_disable()
{
    gpio_deactivate(&blue_strobe.gpio);
    clock_removePeriodicCallback(strobe_blink);
}

void strobe_blink()
{
    uint32_t period_ms = 0;

    switch(blue_strobe.phase) {
    case 1:
        gpio_writePin(&blue_strobe.gpio, false);
        period_ms = STROBE_BLINK_PERIOD_MSEC;
        blue_strobe.phase = 2;
        console_write("phase 1\n");
        break;
    case 2:
        gpio_writePin(&blue_strobe.gpio, true);
        period_ms = STROBE_BLINK_PERIOD_MSEC + 1;
        blue_strobe.phase = 3;
        console_write("phase 2\n");
        break;
    case 3:
        gpio_writePin(&blue_strobe.gpio, false);
        period_ms = STROBE_BLINK_PERIOD_MSEC + 2;
        blue_strobe.phase = 4;
        console_write("phase 3\n");
        break;
    case 4:
        gpio_writePin(&blue_strobe.gpio, true);
        period_ms = STROBE_DELAY_PERIOD_MSEC;
        blue_strobe.phase = 1;
        console_write("phase 4\n");
        break;
    }

     clock_addPeriodicCallback(strobe_blink, period_ms, 1);
}
