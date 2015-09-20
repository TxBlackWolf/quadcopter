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

static GPIOHandle_t orange_strobe;
static GPIOHandle_t red_strobe;
static GPIOHandle_t blue_strobe;
static GPIOHandle_t green_strobe;

bool strobe_init()
{
    GPIOConfig_t config;
    config.direction = GPIO_DIRECTION_OUT;
    config.resistor_type = GPIO_RESISTOR_NONE;

    orange_strobe.port = ORANGE_STROBE_PORT;
    orange_strobe.pin = ORANGE_STROBE_PIN;
    orange_strobe.name = "orange strobe";
    if(!board_strobeInit(&orange_strobe, config))
        return false;

    console_write("lights: Initialized %s (GPIO P%d.%d)\n", orange_strobe.name, orange_strobe.port, orange_strobe.pin);

    red_strobe.port = RED_STROBE_PORT;
    red_strobe.pin = RED_STROBE_PIN;
    red_strobe.name = "red strobe";
    if(!board_strobeInit(&red_strobe, config))
        return false;

    console_write("lights: Initialized %s (GPIO P%d.%d)\n", red_strobe.name, red_strobe.port, red_strobe.pin);

    blue_strobe.port = BLUE_STROBE_PORT;
    blue_strobe.pin = BLUE_STROBE_PIN;
    blue_strobe.name = "blue strobe";
    if(!board_strobeInit(&blue_strobe, config))
        return false;

    console_write("lights: Initialized %s (GPIO P%d.%d)\n", blue_strobe.name, blue_strobe.port, blue_strobe.pin);

    green_strobe.port = GREEN_STROBE_PORT;
    green_strobe.pin = GREEN_STROBE_PIN;
    green_strobe.name = "green strobe";
    if(!board_strobeInit(&green_strobe, config))
        return false;

    console_write("lights: Initialized %s (GPIO P%d.%d)\n", green_strobe.name, green_strobe.port, green_strobe.pin);

    return true;
}

void strobe_blink()
{
    gpio_writePin(&orange_strobe, true);
    for(int i = 0; i < 1000000; ++i);
    gpio_writePin(&orange_strobe, false);

    gpio_writePin(&red_strobe, true);
    for(int i = 0; i < 1000000; ++i);
    gpio_writePin(&red_strobe, false);

    gpio_writePin(&blue_strobe, true);
    for(int i = 0; i < 1000000; ++i);
    gpio_writePin(&blue_strobe, false);

    gpio_writePin(&green_strobe, true);
    for(int i = 0; i < 1000000; ++i);
    gpio_writePin(&green_strobe, false);
}
