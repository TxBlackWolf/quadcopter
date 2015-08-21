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

static GPIOHandle_t strobe_handle;

void strobe_init()
{
    GPIOConfig_t config;
    config.direction = GPIO_DIRECTION_OUT;
    config.resistor_type = GPIO_RESISTOR_NONE;

    strobe_handle = board_strobeInit(STROBE_PORT, STROBE_PIN, config);
}

void strobe_blink()
{
    gpio_writePin(strobe_handle, true);

    volatile int i;
    for(i = 0; i < 100000000; ++i);

    gpio_writePin(strobe_handle, false);
}
