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

static GPIOHandle_t orange_strobe_handle;
static GPIOHandle_t red_strobe_handle;
static GPIOHandle_t blue_strobe_handle;
static GPIOHandle_t green_strobe_handle;

void strobe_init()
{
    GPIOConfig_t config;
    config.direction = GPIO_DIRECTION_OUT;
    config.resistor_type = GPIO_RESISTOR_NONE;

    orange_strobe_handle = board_strobeInit(ORANGE_STROBE_PORT, ORANGE_STROBE_PIN, config);
    red_strobe_handle = board_strobeInit(RED_STROBE_PORT, RED_STROBE_PIN, config);
    blue_strobe_handle = board_strobeInit(BLUE_STROBE_PORT, BLUE_STROBE_PIN, config);
    green_strobe_handle = board_strobeInit(GREEN_STROBE_PORT, GREEN_STROBE_PIN, config);
}

void strobe_blink()
{
    volatile int i;

    gpio_writePin(orange_strobe_handle, true);
    for(i = 0; i < 1000000; ++i);
    gpio_writePin(orange_strobe_handle, false);

    gpio_writePin(red_strobe_handle, true);
    for(i = 0; i < 1000000; ++i);
    gpio_writePin(red_strobe_handle, false);

    gpio_writePin(blue_strobe_handle, true);
    for(i = 0; i < 1000000; ++i);
    gpio_writePin(blue_strobe_handle, false);

    gpio_writePin(green_strobe_handle, true);
    for(i = 0; i < 1000000; ++i);
    gpio_writePin(green_strobe_handle, false);
}
