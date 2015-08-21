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
#include "board/board.h"
#include "drivers/lights/lights.h"
#include "hal/gpio.h"

void strobe_init()
{
    GPIOConfig_t config;
    config.function = PA9_USART1_TX;
    config.mode = GPIO_MODE_OUT;
    config.speed = GPIO_SPEED_50MHz;
    config.output_type = GPIO_OUTPUT_PUSHPULL;
    config.resistor_type = GPIO_RESISTOR_NONE;
    board_strobeInit(&config);

    GPIOHandle_t strobe_handle = gpio_init(config);
}

void strobe_blink()
{
}
