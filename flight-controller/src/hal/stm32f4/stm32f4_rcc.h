//---------------------------------------------------------------------------------------------------------------
//
// Filename   : stm32f4_rcc.h
// Author     : Kuba Sejdak
// Created on : 12.08.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#ifndef STM32F4_RCC_H
#define STM32F4_RCC_H

#include <stdint.h>
#include <stdbool.h>

#include "hal/rcc.h"

// AHB1 peripherals.
#define RCC_AHB1_PERIPHERAL_GPIOA           (1 << 0)
#define RCC_AHB1_PERIPHERAL_GPIOB           (1 << 1)
#define RCC_AHB1_PERIPHERAL_GPIOC           (1 << 2)
#define RCC_AHB1_PERIPHERAL_GPIOD           (1 << 3)
#define RCC_AHB1_PERIPHERAL_GPIOE           (1 << 4)
#define RCC_AHB1_PERIPHERAL_GPIOF           (1 << 5)
#define RCC_AHB1_PERIPHERAL_GPIOG           (1 << 6)
#define RCC_AHB1_PERIPHERAL_GPIOH           (1 << 7)
#define RCC_AHB1_PERIPHERAL_GPIOI           (1 << 8)
#define RCC_AHB1_PERIPHERAL_CRC             (1 << 12)
#define RCC_AHB1_PERIPHERAL_FLITF           (1 << 15)
#define RCC_AHB1_PERIPHERAL_SRAM1           (1 << 16)
#define RCC_AHB1_PERIPHERAL_SRAM2           (1 << 17)
#define RCC_AHB1_PERIPHERAL_BKPSRAM         (1 << 18)
#define RCC_AHB1_PERIPHERAL_CCMDATARAMEN    (1 << 20)
#define RCC_AHB1_PERIPHERAL_DMA1            (1 << 21)
#define RCC_AHB1_PERIPHERAL_DMA2            (1 << 22)
#define RCC_AHB1_PERIPHERAL_ETH_MAC         (1 << 25)
#define RCC_AHB1_PERIPHERAL_ETH_MAC_Tx      (1 << 26)
#define RCC_AHB1_PERIPHERAL_ETH_MAC_Rx      (1 << 27)
#define RCC_AHB1_PERIPHERAL_ETH_MAC_PTP     (1 << 28)
#define RCC_AHB1_PERIPHERAL_OTG_HS          (1 << 29)
#define RCC_AHB1_PERIPHERAL_OTG_HS_ULPI     (1 << 30)

// AHB2 peripherals.
#define RCC_AHB2_PERIPHERAL_DCMI            (1 << 0)
#define RCC_AHB2_PERIPHERAL_CRYP            (1 << 4)
#define RCC_AHB2_PERIPHERAL_HASH            (1 << 5)
#define RCC_AHB2_PERIPHERAL_RNG             (1 << 6)
#define RCC_AHB2_PERIPHERAL_OTG_FS          (1 << 7)

// AHB3 peripherals.
#define RCC_AHB3_PERIPHERAL_FSMC            (1 << 0)

// APB1 peripherals.
#define RCC_APB1_PERIPHERAL_TIM2            (1 << 0)
#define RCC_APB1_PERIPHERAL_TIM3            (1 << 1)
#define RCC_APB1_PERIPHERAL_TIM4            (1 << 2)
#define RCC_APB1_PERIPHERAL_TIM5            (1 << 3)
#define RCC_APB1_PERIPHERAL_TIM6            (1 << 4)
#define RCC_APB1_PERIPHERAL_TIM7            (1 << 5)
#define RCC_APB1_PERIPHERAL_TIM12           (1 << 6)
#define RCC_APB1_PERIPHERAL_TIM13           (1 << 7)
#define RCC_APB1_PERIPHERAL_TIM14           (1 << 8)
#define RCC_APB1_PERIPHERAL_WWDG            (1 << 11)
#define RCC_APB1_PERIPHERAL_SPI2            (1 << 14)
#define RCC_APB1_PERIPHERAL_SPI3            (1 << 15)
#define RCC_APB1_PERIPHERAL_USART2          (1 << 17)
#define RCC_APB1_PERIPHERAL_USART3          (1 << 18)
#define RCC_APB1_PERIPHERAL_UART4           (1 << 19)
#define RCC_APB1_PERIPHERAL_UART5           (1 << 20)
#define RCC_APB1_PERIPHERAL_I2C1            (1 << 21)
#define RCC_APB1_PERIPHERAL_I2C2            (1 << 22)
#define RCC_APB1_PERIPHERAL_I2C3            (1 << 23)
#define RCC_APB1_PERIPHERAL_CAN1            (1 << 25)
#define RCC_APB1_PERIPHERAL_CAN2            (1 << 26)
#define RCC_APB1_PERIPHERAL_PWR             (1 << 28)
#define RCC_APB1_PERIPHERAL_DAC             (1 << 29)

// APB2 peripherals.
#define RCC_APB2_PERIPHERAL_TIM1            (1 << 0)
#define RCC_APB2_PERIPHERAL_TIM8            (1 << 1)
#define RCC_APB2_PERIPHERAL_USART1          (1 << 4)
#define RCC_APB2_PERIPHERAL_USART6          (1 << 5)
#define RCC_APB2_PERIPHERAL_ADC             (1 << 8)
#define RCC_APB2_PERIPHERAL_ADC1            (1 << 8)
#define RCC_APB2_PERIPHERAL_ADC2            (1 << 9)
#define RCC_APB2_PERIPHERAL_ADC3            (1 << 10)
#define RCC_APB2_PERIPHERAL_SDIO            (1 << 11)
#define RCC_APB2_PERIPHERAL_SPI1            (1 << 12)
#define RCC_APB2_PERIPHERAL_SYSCFG          (1 << 14)
#define RCC_APB2_PERIPHERAL_TIM9            (1 << 16)
#define RCC_APB2_PERIPHERAL_TIM10           (1 << 17)
#define RCC_APB2_PERIPHERAL_TIM11           (1 << 18)

// SYSCLK clock.
#define RCC_SYSCLK_SOURCE_HSI               0
#define RCC_SYSCLK_SOURCE_HSE               (1 << 0)
#define RCC_SYSCLK_SOURCE_PLLCLK            (1 << 1)

#define RCC_SYSCLK_SOURCE_USED_HSI          0
#define RCC_SYSCLK_SOURCE_USED_HSE          (1 << 2)
#define RCC_SYSCLK_SOURCE_USED_PLLCLK       (1 << 3)

// PLL clock.
#define RCC_PLL_SOURCE_HSI                  0
#define RCC_PLL_SOURCE_HSE                  (1 << 22)

// Clock frequencies structure.
typedef struct
{
  uint32_t sysclk_frequency_hz;
  uint32_t hclk_frequency_hz;
  uint32_t pclk1_frequency_hz;
  uint32_t pclk2_frequency_hz;
} STM32F4_ClockFrequencies_t;

void stm32f4_rccEnablePeripheralClockAHB1(uint32_t peripheral, bool enabled);
void stm32f4_rccEnablePeripheralClockAHB2(uint32_t peripheral, bool enabled);
void stm32f4_rccEnablePeripheralClockAHB3(uint32_t peripheral, bool enabled);
void stm32f4_rccEnablePeripheralClockAPB1(uint32_t peripheral, bool enabled);
void stm32f4_rccEnablePeripheralClockAPB2(uint32_t peripheral, bool enabled);

void stm32f4_rccResetPeripheralAHB1(uint32_t peripheral, bool enabled);
void stm32f4_rccResetPeripheralAHB2(uint32_t peripheral, bool enabled);
void stm32f4_rccResetPeripheralAHB3(uint32_t peripheral, bool enabled);
void stm32f4_rccResetPeripheralAPB1(uint32_t peripheral, bool enabled);
void stm32f4_rccResetPeripheralAPB2(uint32_t peripheral, bool enabled);

void stm32f4_rccGetClocksFrequencies(STM32F4_ClockFrequencies_t *clocks);

#endif
