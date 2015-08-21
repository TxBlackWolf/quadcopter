//---------------------------------------------------------------------------------------------------------------
//
// Filename   : gpio.h
// Author     : Kuba Sejdak
// Created on : 11.08.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include <stdbool.h>

//---------------------------------------------------------------------------------------------------------------
// BASIC PIN CONFIGURATION
//---------------------------------------------------------------------------------------------------------------

// Pin port.
typedef enum
{
    GPIO_PORT_A,
    GPIO_PORT_B,
    GPIO_PORT_C,
    GPIO_PORT_D,
    GPIO_PORT_E,
    GPIO_PORT_F,
    GPIO_PORT_G,
    GPIO_PORT_H,
    GPIO_PORT_I,
} GPIOPort_t;

// Pin number.
typedef enum
{
    GPIO_PIN_0  = (1 << 0),
    GPIO_PIN_1  = (1 << 1),
    GPIO_PIN_2  = (1 << 2),
    GPIO_PIN_3  = (1 << 3),
    GPIO_PIN_4  = (1 << 4),
    GPIO_PIN_5  = (1 << 5),
    GPIO_PIN_6  = (1 << 6),
    GPIO_PIN_7  = (1 << 7),
    GPIO_PIN_8  = (1 << 8),
    GPIO_PIN_9  = (1 << 9),
    GPIO_PIN_10 = (1 << 10),
    GPIO_PIN_11 = (1 << 11),
    GPIO_PIN_12 = (1 << 12),
    GPIO_PIN_13 = (1 << 13),
    GPIO_PIN_14 = (1 << 14),
    GPIO_PIN_15 = (1 << 15)
} GPIOPin_t;

// Pin mode.
typedef enum
{
    GPIO_MODE_IN        = 0x00,
    GPIO_MODE_OUT       = 0x01,
    GPIO_MODE_ALTERNATE = 0x02,
    GPIO_MODE_ANALOG    = 0x03
} GPIOMode_t;

// Pin speed.
// === DEVICE
typedef enum
{
    GPIO_SPEED_2MHz   = 0x00,   // Low speed.
    GPIO_SPEED_25MHz  = 0x01,   // Medium speed.
    GPIO_SPEED_50MHz  = 0x02,   // Fast speed.
    GPIO_SPEED_100MHz = 0x03    // High speed on 30 pF (80 MHz output max speed on 15 pF).
} GPIOSpeed_t;

// Pin output type.
// === DEVICE
typedef enum
{
    GPIO_OUTPUT_PUSHPULL  = 0x00,
    GPIO_OUTPUT_OPENDRAIN = 0x01
} GPIOOutputType_t;

// Pullup/pulldown resistors.
typedef enum
{
    GPIO_RESISTOR_NONE     = 0x00,
    GPIO_RESISTOR_PULLUP   = 0x01,
    GPIO_RESISTOR_PULLDOWN = 0x02
} GPIOResistorType_t;

// Configuration structure.
typedef struct
{
    GPIOPort_t port;
    GPIOPin_t pin;
    uint8_t function;
    GPIOMode_t mode;
    GPIOSpeed_t speed;
    GPIOOutputType_t output_type;
    GPIOResistorType_t resistor_type;
} GPIOConfig_t;

// Pin handle.
typedef struct
{
    GPIOPort_t port;
    GPIOPin_t pin;
} GPIOHandle_t;

#if 0
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
#endif

GPIOHandle_t gpio_init(GPIOConfig_t config);
void gpio_deactivate(GPIOHandle_t handle);

bool gpio_readPin(GPIOHandle_t handle);
uint16_t gpio_readPort(GPIOPort_t port);

bool gpio_writePin(GPIOHandle_t handle, bool value);
bool gpio_writePort(GPIOPort_t port, uint16_t value);

void gpio_pinConfigLock(GPIOHandle_t handle);

#endif
