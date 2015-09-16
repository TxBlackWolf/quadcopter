//---------------------------------------------------------------------------------------------------------------
//
// Filename   : stm32f4_discovery_pinout.h
// Author     : Kuba Sejdak
// Created on : 21.08.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#ifndef STM32F4_DISCOVERY_PINOUT_H
#define STM32F4_DISCOVERY_PINOUT_H

#include "board/board_drivers_support.h"
#include "hal/stm32f4/stm32f4_gpio.h"
#include "hal/stm32f4/stm32f4_uart.h"
#include "hal/stm32f4/stm32f4_timer.h"

// UART console.
#define UART_CONSOLE_DEVICE             STM32F4_UART_4
#define UART_CONSOLE_PORT               STM32F4_GPIO_PORT_C
#define UART_CONSOLE_PIN                STM32F4_GPIO_PIN_10

#if ACCELEROMETER_ENABLED
// TODO: implement
#endif

#if BAROMETER_ENABLED
// TODO: implement
#endif

#if BUZZER_ENABLED
// TODO: implement
#endif

#if CAMERA_ENABLED
// TODO: implement
#endif

#if ENGINES_ENABLED
    // Front left.
    #define ENGINE_FRONT_LEFT_PORT      STM32F4_GPIO_PORT_A
    #define ENGINE_FRONT_LEFT_PIN       STM32F4_GPIO_PIN_15
    #define ENGINE_FRONT_LEFT_TIMER     STM32F4_TIMER_2
#endif

#if GYROSCOPE_ENABLED
// TODO: implement
#endif

#if LIGHTS_ENABLED
    // Strobe.
    #define ORANGE_STROBE_PORT          STM32F4_GPIO_PORT_D
    #define ORANGE_STROBE_PIN           STM32F4_GPIO_PIN_13
    #define RED_STROBE_PORT             STM32F4_GPIO_PORT_D
    #define RED_STROBE_PIN              STM32F4_GPIO_PIN_14
    #define BLUE_STROBE_PORT            STM32F4_GPIO_PORT_D
    #define BLUE_STROBE_PIN             STM32F4_GPIO_PIN_15
    #define GREEN_STROBE_PORT           STM32F4_GPIO_PORT_D
    #define GREEN_STROBE_PIN            STM32F4_GPIO_PIN_12
#endif

#if MAGNETOMETER_ENABLED
// TODO: implement
#endif

#endif
