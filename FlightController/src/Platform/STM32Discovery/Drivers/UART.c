//---------------------------------------------------------------------------------------------------------------
//
// Filename   : UART.c
// Author     : Kuba Sejdak
// Created on : 11.08.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#include "UART.h"
#include "RCC.h"
#include "GPIO.h"

bool UARTInit(UARTDevice_t device, UARTDirection_t direction)
{
    // Enable clock for GPIO port A.
    RCCEnablePeripheralClockAHB1(RCC_AHB1_PERIPHERAL_GPIOA, true);

    // Configure pin.
    GPIOConfig_t config;
    config.port = GPIO_PORT_A;
    config.pin = GPIO_PIN_9;
    config.function = PA9_USART1_TX;
    config.mode = GPIO_MODE_ALTERNATE;
    config.speed = GPIO_SPEED_100MHz;
    config.output_type = GPIO_OUTPUT_PUSHPULL;
    config.resistor_type = GPIO_RESISTOR_PULLUP;

    GPIOHandle_t tx_handle = GPIOInit(config);

    return true;
}
