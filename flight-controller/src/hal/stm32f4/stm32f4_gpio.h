//---------------------------------------------------------------------------------------------------------------
//
// Filename   : stm32f4_gpio.h
// Author     : Kuba Sejdak
// Created on : 11.08.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#ifndef STM32F4_GPIO_H
#define STM32F4_GPIO_H

#include "hal/gpio.h"

#include <stdint.h>

// Pin port.
#define STM32F4_GPIO_PORT_A     0
#define STM32F4_GPIO_PORT_B     1
#define STM32F4_GPIO_PORT_C     2
#define STM32F4_GPIO_PORT_D     3
#define STM32F4_GPIO_PORT_E     4
#define STM32F4_GPIO_PORT_F     5
#define STM32F4_GPIO_PORT_G     6
#define STM32F4_GPIO_PORT_H     7
#define STM32F4_GPIO_PORT_I     8

// Pin number.
#define STM32F4_GPIO_PIN_0      0
#define STM32F4_GPIO_PIN_1      1
#define STM32F4_GPIO_PIN_2      2
#define STM32F4_GPIO_PIN_3      3
#define STM32F4_GPIO_PIN_4      4
#define STM32F4_GPIO_PIN_5      5
#define STM32F4_GPIO_PIN_6      6
#define STM32F4_GPIO_PIN_7      7
#define STM32F4_GPIO_PIN_8      8
#define STM32F4_GPIO_PIN_9      9
#define STM32F4_GPIO_PIN_10     10
#define STM32F4_GPIO_PIN_11     11
#define STM32F4_GPIO_PIN_12     12
#define STM32F4_GPIO_PIN_13     13
#define STM32F4_GPIO_PIN_14     14
#define STM32F4_GPIO_PIN_15     15

// GPIO pin mode.
typedef enum
{
    GPIO_MODE_IN        = 0x00,
    GPIO_MODE_OUT       = 0x01,
    GPIO_MODE_ALTERNATE = 0x02,
    GPIO_MODE_ANALOG    = 0x03
} STM32F4_GPIOMode_t;

// GPIO pin speed.
typedef enum
{
    GPIO_SPEED_2MHz   = 0x00,   // Low speed.
    GPIO_SPEED_25MHz  = 0x01,   // Medium speed.
    GPIO_SPEED_50MHz  = 0x02,   // Fast speed.
    GPIO_SPEED_100MHz = 0x03    // High speed on 30 pF (80 MHz output max speed on 15 pF).
} STM32F4_GPIOSpeed_t;

// GPIO pin output type.
typedef enum
{
    GPIO_OUTPUT_PUSHPULL  = 0x00,
    GPIO_OUTPUT_OPENDRAIN = 0x01
} STM32F4_GPIOOutputType_t;

// GPIO pin configuration structure.
typedef struct
{
    GPIOConfig_t general_config;
    int function;
    STM32F4_GPIOMode_t mode;
    STM32F4_GPIOSpeed_t speed;
    STM32F4_GPIOOutputType_t output_type;
} STM32F4_GPIOConfig_t;

bool stm32f4_gpioInit(GPIOHandle_t handle, STM32F4_GPIOConfig_t config);

#endif
