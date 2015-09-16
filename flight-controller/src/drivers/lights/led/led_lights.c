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

static GPIOHandle_t orange_strobe_handle;
static GPIOHandle_t red_strobe_handle;
static GPIOHandle_t blue_strobe_handle;
static GPIOHandle_t green_strobe_handle;

bool strobe_init()
{
    GPIOConfig_t config;
    config.direction = GPIO_DIRECTION_OUT;
    config.resistor_type = GPIO_RESISTOR_NONE;

    orange_strobe_handle.port = ORANGE_STROBE_PORT;
    orange_strobe_handle.pin = ORANGE_STROBE_PIN;
    if(!board_strobeInit(orange_strobe_handle, config))
        return false;

    console_write("lights: Initialized orange strobe light (GPIO P%d.%d)\n", ORANGE_STROBE_PORT, ORANGE_STROBE_PIN);

    red_strobe_handle.port = RED_STROBE_PORT;
    red_strobe_handle.pin = RED_STROBE_PIN;
    if(!board_strobeInit(red_strobe_handle, config))
        return false;

    console_write("lights: Initialized red strobe light (GPIO P%d.%d)\n", RED_STROBE_PORT, RED_STROBE_PIN);

    blue_strobe_handle.port = BLUE_STROBE_PORT;
    blue_strobe_handle.pin = BLUE_STROBE_PIN;
    if(!board_strobeInit(blue_strobe_handle, config))
        return false;

    console_write("lights: Initialized blue strobe light (GPIO P%d.%d)\n", BLUE_STROBE_PORT, BLUE_STROBE_PIN);

    green_strobe_handle.port = GREEN_STROBE_PORT;
    green_strobe_handle.pin = GREEN_STROBE_PIN;
    if(!board_strobeInit(green_strobe_handle, config))
        return false;

    console_write("lights: Initialized blue strobe light (GPIO P%d.%d)\n", GREEN_STROBE_PORT, GREEN_STROBE_PIN);

    return true;
}

void strobe_blink()
{
    gpio_writePin(orange_strobe_handle, true);
    for(int i = 0; i < 1000000; ++i);
    gpio_writePin(orange_strobe_handle, false);

    gpio_writePin(red_strobe_handle, true);
    for(int i = 0; i < 1000000; ++i);
    gpio_writePin(red_strobe_handle, false);

    gpio_writePin(blue_strobe_handle, true);
    for(int i = 0; i < 1000000; ++i);
    gpio_writePin(blue_strobe_handle, false);

    gpio_writePin(green_strobe_handle, true);
    for(int i = 0; i < 1000000; ++i);
    gpio_writePin(green_strobe_handle, false);
}
