////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       22.07.2015
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "uart_console.h"
#include "stm32f4_discovery_pinout.h"
#include "hal/stm32f4/stm32f4_gpio.h"
#include "hal/stm32f4/stm32f4_gpio_functions.h"
#include "hal/stm32f4/stm32f4_uart.h"
#include "hal/uart.h"
#include "utils/misc/string_manipulation.h"

#include <stdarg.h>
#include <stdlib.h>

#define CONSOLE_BUFFER_SIZE     1024
#define CONSOLE_BAUD_RATE       115200

static UARTHandle_t uart_handle;
static bool console_initialized = false;

bool console_init()
{
    uart_handle.device = UART_CONSOLE_DEVICE;
    uart_handle.uart_gpio.port = UART_CONSOLE_PORT;
    uart_handle.uart_gpio.pin = UART_CONSOLE_PIN;

    // Configure GPIO.
    STM32F4_GPIOConfig_t gpio_config;
    gpio_config.general_config.direction = GPIO_DIRECTION_OUT;
    gpio_config.general_config.resistor_type = GPIO_RESISTOR_PULLUP;
    gpio_config.function = stm32f4_uartToPinFunction(&uart_handle);
    gpio_config.speed = GPIO_SPEED_100MHz;
    gpio_config.mode = GPIO_MODE_ALTERNATE;
    gpio_config.output_type = GPIO_OUTPUT_PUSHPULL;

    if(!stm32f4_gpioInit(&uart_handle.uart_gpio, &gpio_config))
        return false;

    // Configure UART.
    STM32F4_UARTConfig_t uart_config;
    uart_config.general_config.protocol.baud_rate = CONSOLE_BAUD_RATE;
    uart_config.general_config.protocol.data_bits = UART_DATA_BITS_8;
    uart_config.general_config.protocol.stop_bits = UART_STOP_BITS_1;
    uart_config.general_config.protocol.parity = UART_PARTITY_NONE;
    uart_config.general_config.protocol.flow_control = UART_FLOW_CONTROL_NONE;
    uart_config.general_config.direction = UART_DIRECTION_WRITE;
    uart_config.general_config.mode = UART_MODE_ASYNCHRONOUS;

    console_initialized = stm32f4_uartInit(&uart_handle, &uart_config);
    if(console_initialized) {
        uart_activate(&uart_handle);
        console_write("\n");
    }

    return console_initialized;
}

void console_write(const char *format, ...)
{
    if(!console_initialized)
        return;

    char buffer[CONSOLE_BUFFER_SIZE];

    va_list args;
    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);

    for(int i = 0; buffer[i]; ++i)
        uart_send(&uart_handle, buffer[i]);
}
