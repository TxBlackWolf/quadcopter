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
#include "board/console.h"

#define STROBE_DELAY_PERIOD_MSEC    2000
#define STROBE_BLINK_PERIOD_MSEC    150

typedef struct {
    GPIOHandle_t gpio;
    TimerHandle_t timer;
    bool state;
    uint8_t phase;
} StrobeLight_t;

static StrobeLight_t blue_strobe;

bool strobe_init()
{
    blue_strobe.gpio.port = BLUE_STROBE_PORT;
    blue_strobe.gpio.pin = BLUE_STROBE_PIN;
    blue_strobe.gpio.name = "blue strobe";
    blue_strobe.timer.device = BLUE_STROBE_TIMER;
    blue_strobe.timer.channel = BLUE_STROBE_TIMER_CHANNEL;
    blue_strobe.state = false;
    blue_strobe.phase = 1;

    GPIOConfig_t gpio_config;
    gpio_config.direction = GPIO_DIRECTION_OUT;
    gpio_config.resistor_type = GPIO_RESISTOR_NONE;

    TimerConfig_t timer_config;
    timer_config.use_period = true;
    timer_config.period_ms = STROBE_DELAY_PERIOD_MSEC;

    if(!board_strobeInit(&blue_strobe.gpio, gpio_config, &blue_strobe.timer, timer_config))
        return false;

    timer_registerEventCallback(&blue_strobe.timer, strobe_blink);
    strobe_enable();

    console_write("lights: Initialized %s (GPIO P%d.%d)\n", blue_strobe.gpio.name, blue_strobe.gpio.port, blue_strobe.gpio.pin);
    return true;
}

void strobe_enable()
{
    timer_activate(&blue_strobe.timer);
    gpio_activate(&blue_strobe.gpio);
}

void strobe_disable()
{
    gpio_deactivate(&blue_strobe.gpio);
    timer_deactivate(&blue_strobe.timer);
}

void strobe_blink()
{
    TimerConfig_t config;
    config.use_period = true;

    switch(blue_strobe.phase) {
    case 1:
        gpio_writePin(&blue_strobe.gpio, false);
        config.period_ms = STROBE_BLINK_PERIOD_MSEC;
        blue_strobe.phase = 2;
        break;
    case 2:
        gpio_writePin(&blue_strobe.gpio, true);
        config.period_ms = STROBE_BLINK_PERIOD_MSEC;
        blue_strobe.phase = 3;
        break;
    case 3:
        gpio_writePin(&blue_strobe.gpio, false);
        config.period_ms = STROBE_BLINK_PERIOD_MSEC;
        blue_strobe.phase = 4;
        break;
    case 4:
        gpio_writePin(&blue_strobe.gpio, true);
        config.period_ms = STROBE_DELAY_PERIOD_MSEC;
        blue_strobe.phase = 1;
        break;
    }

    timer_setEventFrequency(&blue_strobe.timer, config);
}
