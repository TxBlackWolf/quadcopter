//---------------------------------------------------------------------------------------------------------------
//
// Filename   : uart.c
// Author     : Kuba Sejdak
// Created on : 11.08.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#include "hal/uart.h"
#include "hal/rcc.h"
#include "hal/gpio.h"

bool uart_init(UARTDevice_t device, UARTDirection_t direction)
{
    // Enable clock for GPIO port A.
    rcc_enablePeripheralClockAHB1(RCC_AHB1_PERIPHERAL_GPIOA, true);

    // Configure pin.
    GPIOConfig_t config;
    config.port = GPIO_PORT_A;
    config.pin = GPIO_PIN_9;
    config.function = PA9_USART1_TX;
    config.mode = GPIO_MODE_ALTERNATE;
    config.speed = GPIO_SPEED_100MHz;
    config.output_type = GPIO_OUTPUT_PUSHPULL;
    config.resistor_type = GPIO_RESISTOR_PULLUP;

    GPIOHandle_t tx_handle = gpio_init(config);

    return true;
}
