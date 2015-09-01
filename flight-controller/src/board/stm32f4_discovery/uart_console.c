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

#include "hal/stm32f4/misc.h"
#include "hal/stm32f4/stm32f4xx_gpio.h"
#include "hal/stm32f4/stm32f4xx_rcc.h"
#include "hal/stm32f4/stm32f4xx_usart.h"

static UARTHandle_t uart_handle;

bool console_init()
{
#if 0
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

    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = UART4_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(&NVIC_InitStruct);

    return stm32f4_uartInit(uart_config, uart_handle.device);
#else
    GPIO_InitTypeDef     GPIO_InitStruct;

    // Enable clock for GPIOA
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    /**
    * Tell pins PA9 and PA10 which alternating function you will use
    * @important Make sure, these lines are before pins configuration!
    */
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
    // Initialize pins as alternating function
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    NVIC_InitTypeDef NVIC_InitStruct;

    /**
     * Enable clock for USART1 peripheral
     */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    /**
     * Set Baudrate to value you pass to function
     * Disable Hardware Flow control
     * Set Mode To TX and RX, so USART will work in full-duplex mode
     * Disable parity bit
     * Set 1 stop bit
     * Set Data bits to 8
     *
     * Initialize USART1
     * Activate USART1
     */

    USART_InitTypeDef USART_InitStruct;
    USART_InitStruct.USART_BaudRate = 9600;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1, &USART_InitStruct);
    USART_Cmd(USART1, ENABLE);

    /**
     * Enable RX interrupt
     */
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    /**
     * Set Channel to USART1
     * Set Channel Cmd to enable. That will enable USART1 channel in NVIC
     * Set Both priorities to 0. This means high priority
     *
     * Initialize NVIC
     */
    NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(&NVIC_InitStruct);
    return true;
#endif
}

int console_write(const char *format, ...)
{
    // TODO: implement.
    uart_send(uart_handle, 'A');
    USART_SendData(USART1, 'A');
    return 0;
}

