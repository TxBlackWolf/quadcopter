 //---------------------------------------------------------------------------------------------------------------
//
// Filename   : stm32f4_discovery.c
// Author     : Kuba Sejdak
// Created on : 22.07.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#include "board/board.h"
#include "stm32f4_discovery.h"
#include "hal/stm32f4/stm32f4_gpio.h"

bool board_init()
{
    // TODO: implement.
    return false;
}

GPIOHandle_t board_strobeInit(GPIOPort_t port, GPIOPort_t pin, GPIOConfig_t config)
{
    STM32F4_GPIOConfig_t pin_config;
    pin_config.general_config = config;
    pin_config.function = PA9_USART1_TX;
    pin_config.speed = GPIO_SPEED_50MHz;
    pin_config.mode = GPIO_MODE_OUT;
    pin_config.output_type = GPIO_OUTPUT_PUSHPULL;

    return stm32f4_gpioInit(port, pin, pin_config);
}
