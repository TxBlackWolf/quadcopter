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

//---------------------------------------------------------------------------------------------------------------
// STM32F4 PIN CONFIGURATION
//---------------------------------------------------------------------------------------------------------------

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

// Pin mode.
typedef enum
{
    GPIO_MODE_IN        = 0x00,
    GPIO_MODE_OUT       = 0x01,
    GPIO_MODE_ALTERNATE = 0x02,
    GPIO_MODE_ANALOG    = 0x03
} STM32F4_GPIOMode_t;

// Pin speed.
typedef enum
{
    GPIO_SPEED_2MHz   = 0x00,   // Low speed.
    GPIO_SPEED_25MHz  = 0x01,   // Medium speed.
    GPIO_SPEED_50MHz  = 0x02,   // Fast speed.
    GPIO_SPEED_100MHz = 0x03    // High speed on 30 pF (80 MHz output max speed on 15 pF).
} STM32F4_GPIOSpeed_t;

// Pin output type.
typedef enum
{
    GPIO_OUTPUT_PUSHPULL  = 0x00,
    GPIO_OUTPUT_OPENDRAIN = 0x01
} STM32F4_GPIOOutputType_t;

// STM32F4 pin configuration structure.
typedef struct
{
    GPIOConfig_t general_config;
    uint8_t function;
    STM32F4_GPIOMode_t mode;
    STM32F4_GPIOSpeed_t speed;
    STM32F4_GPIOOutputType_t output_type;
} STM32F4_GPIOConfig_t;


//---------------------------------------------------------------------------------------------------------------
// PORT A PINS ALTERNATE FUNCTIONS
//---------------------------------------------------------------------------------------------------------------

// PA0
#define PA0_TIM2_CH1_ETR    1
#define PA0_TIM5_CH1        2
#define PA0_TIM8_ETR        3
#define PA0_USART2_CTS      7
#define PA0_UART4_TX        8
#define PA0_ETH_MII_CRS     11
#define PA0_EVENTOUT        15

// PA1
#define PA1_TIM2_CH2        1
#define PA1_TIM5_CH2        2
#define PA1_USART2_RTS      7
#define PA1_UART4_RX        8
#define PA1_ETH_MII_RX_CLK  11
#define PA1_EVENTOUT        15

// PA2
#define PA2_TIM2_CH3        1
#define PA2_TIM5_CH3        2
#define PA2_TIM9_CH1        3
#define PA2_USART2_TX       7
#define PA2_ETH_MDIO        11
#define PA2_EVENTOUT        15

// PA3
#define PA3_TIM2_CH4        1
#define PA3_TIM5_CH4        2
#define PA3_TIM9_CH2        3
#define PA3_USART2_RX       7
#define PA3_OTG_HS_ULPI_D0  10
#define PA3_ETH_MII_COL     11
#define PA3_EVENTOUT        15

// PA4
// TODO: implement

// PA5
// TODO: implement

// PA6
// TODO: implement

// PA7
// TODO: implement

// PA8
// TODO: implement

// PA9
#define PA9_TIM1_CH2        1
#define PA9_I2C3_SMBA       4
#define PA9_USART1_TX       7
#define PA9_DCMI_D0         13
#define PA9_EVENTOUT        15

// PA10
// TODO: implement

// PA11
// TODO: implement

// PA12
// TODO: implement

// PA13
// TODO: implement

// PA14
// TODO: implement

// PA15
// TODO: implement

GPIOHandle_t stm32f4_gpioInit(GPIOPort_t port, GPIOPort_t pin, STM32F4_GPIOConfig_t config);

#endif
