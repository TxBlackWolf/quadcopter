////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       21.08.2015
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef STM32F4_DISCOVERY_PINOUT_H
#define STM32F4_DISCOVERY_PINOUT_H

#include "hal/stm32f4/stm32f4_gpio.h"
#include "hal/stm32f4/stm32f4_timer.h"
#include "hal/stm32f4/stm32f4_uart.h"

// UART console.
#define CONSOLE_UART_DEVICE                     STM32F4_UART_4
#define CONSOLE_GPIO_TX_PORT                    STM32F4_GPIO_PORT_C
#define CONSOLE_GPIO_TX_PIN                     STM32F4_GPIO_PIN_10

// UART commands.
#define COMMANDS_UART_DEVICE                    STM32F4_UART_5
#define COMMANDS_GPIO_TX_PORT                   STM32F4_GPIO_PORT_C
#define COMMANDS_GPIO_TX_PIN                    STM32F4_GPIO_PIN_12
#define COMMANDS_GPIO_RX_PORT                   STM32F4_GPIO_PORT_D
#define COMMANDS_GPIO_RX_PIN                    STM32F4_GPIO_PIN_2

// Periodic timer.
#define PERIODIC_EVENT_TIMER                    STM32F4_TIMER_4
#define PERIODIC_EVENT_TIMER_CHANNEL            1

// Engines.
#define ENGINE_FRONT_LEFT_PORT                  STM32F4_GPIO_PORT_B
#define ENGINE_FRONT_LEFT_PIN                   STM32F4_GPIO_PIN_4
#define ENGINE_FRONT_LEFT_TIMER                 STM32F4_TIMER_3
#define ENGINE_FRONT_LEFT_TIMER_CHANNEL         1

#define ENGINE_FRONT_RIGHT_PORT                 STM32F4_GPIO_PORT_B
#define ENGINE_FRONT_RIGHT_PIN                  STM32F4_GPIO_PIN_5
#define ENGINE_FRONT_RIGHT_TIMER                STM32F4_TIMER_3
#define ENGINE_FRONT_RIGHT_TIMER_CHANNEL        2

#define ENGINE_REAR_LEFT_PORT                   STM32F4_GPIO_PORT_B
#define ENGINE_REAR_LEFT_PIN                    STM32F4_GPIO_PIN_0
#define ENGINE_REAR_LEFT_TIMER                  STM32F4_TIMER_3
#define ENGINE_REAR_LEFT_TIMER_CHANNEL          3

#define ENGINE_REAR_RIGHT_PORT                  STM32F4_GPIO_PORT_B
#define ENGINE_REAR_RIGHT_PIN                   STM32F4_GPIO_PIN_1
#define ENGINE_REAR_RIGHT_TIMER                 STM32F4_TIMER_3
#define ENGINE_REAR_RIGHT_TIMER_CHANNEL         4

// Strobe light.
#define LED_STROBE_PORT                         STM32F4_GPIO_PORT_D
#define LED_STROBE_PIN                          STM32F4_GPIO_PIN_15

#endif
