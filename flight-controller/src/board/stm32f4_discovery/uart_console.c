//---------------------------------------------------------------------------------------------------------------
//
// Filename   : uart_console.c
// Author     : Kuba Sejdak
// Created on : 22.07.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#include "uart_console.h"
#include "stm32f4_discovery_pinout.h"
#include "board/console.h"
#include "hal/uart.h"
#include "hal/stm32f4/stm32f4_gpio.h"
#include "hal/stm32f4/stm32f4_gpio_functions.h"
#include "hal/stm32f4/stm32f4_uart.h"

static UARTHandle_t uart_handle;

bool console_init()
{
    uart_handle.device = UART_CONSOLE_DEVICE;
    uart_handle.uart_gpio.port = UART_CONSOLE_PORT;
    uart_handle.uart_gpio.pin = UART_CONSOLE_PIN;

    // Configure GPIO.
    STM32F4_GPIOConfig_t gpio_config;
    gpio_config.general_config.direction = GPIO_DIRECTION_OUT;
    gpio_config.general_config.resistor_type = GPIO_RESISTOR_PULLUP;
    gpio_config.function = GPIO_AF_UART4;
    gpio_config.speed = GPIO_SPEED_100MHz;
    gpio_config.mode = GPIO_MODE_ALTERNATE;
    gpio_config.output_type = GPIO_OUTPUT_PUSHPULL;

    if(!stm32f4_gpioInit(gpio_config, uart_handle.uart_gpio))
        return false;

    // Configure UART.
    STM32F4_UARTConfig_t uart_config;
    uart_config.general_config.protocol.baud_rate = 115200;
    uart_config.general_config.protocol.data_bits = UART_DATA_BITS_8;
    uart_config.general_config.protocol.stop_bits = UART_STOP_BITS_1;
    uart_config.general_config.protocol.parity = UART_PARTITY_NONE;
    uart_config.general_config.protocol.flow_control = UART_FLOW_CONTROL_NONE;
    uart_config.general_config.direction = UART_DIRECTION_WRITE;
    uart_config.general_config.mode = UART_MODE_ASYNCHRONOUS;

    return stm32f4_uartInit(uart_config, uart_handle.device);
}

int console_write(const char *format, ...)
{
    // TODO: implement.
    uart_send(uart_handle, 'A');
    return 0;
}

