//---------------------------------------------------------------------------------------------------------------
//
// Filename   : stm32f4_gpio_functions.h
// Author     : Kuba Sejdak
// Created on : 23.08.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#ifndef STM32F4_GPIO_FUNCTIONS_H
#define STM32F4_GPIO_FUNCTIONS_H

#define GPIO_DIGITAL_PIN    -1

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
