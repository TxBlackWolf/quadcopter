////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       12.08.2015
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "stm32f4_rcc.h"
#include "CMSIS/stm32f4xx.h"

static uint8_t stm32f4_APBAHB_prescaler_table[16] = {0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9};

//=============================================================================================
// INTERFACE FUNCTIONS
//=============================================================================================

void stm32f4_rccEnablePeripheralClockAHB1(uint32_t peripheral, bool enabled)
{
    if (enabled)
        RCC->AHB1ENR |= peripheral;
    else
        RCC->AHB1ENR &= ~peripheral;
}

void stm32f4_rccEnablePeripheralClockAHB2(uint32_t peripheral, bool enabled)
{
    if (enabled)
        RCC->AHB2ENR |= peripheral;
    else
        RCC->AHB2ENR &= ~peripheral;
}

void stm32f4_rccEnablePeripheralClockAHB3(uint32_t peripheral, bool enabled)
{
    if (enabled)
        RCC->AHB3ENR |= peripheral;
    else
        RCC->AHB3ENR &= ~peripheral;
}

void stm32f4_rccEnablePeripheralClockAPB1(uint32_t peripheral, bool enabled)
{
    if (enabled)
        RCC->APB1ENR |= peripheral;
    else
        RCC->APB1ENR &= ~peripheral;
}

void stm32f4_rccEnablePeripheralClockAPB2(uint32_t peripheral, bool enabled)
{
    if (enabled)
        RCC->APB2ENR |= peripheral;
    else
        RCC->APB2ENR &= ~peripheral;
}

void stm32f4_rccResetPeripheralAHB1(uint32_t peripheral, bool enabled)
{
    if (enabled)
        RCC->AHB1RSTR |= peripheral;
    else
        RCC->AHB1RSTR &= ~peripheral;
}

void stm32f4_rccResetPeripheralAHB2(uint32_t peripheral, bool enabled)
{
    if (enabled)
        RCC->AHB2RSTR |= peripheral;
    else
        RCC->AHB2RSTR &= ~peripheral;
}

void stm32f4_rccResetPeripheralAHB3(uint32_t peripheral, bool enabled)
{
    if (enabled)
        RCC->AHB3RSTR |= peripheral;
    else
        RCC->AHB3RSTR &= ~peripheral;
}

void stm32f4_rccResetPeripheralAPB1(uint32_t peripheral, bool enabled)
{
    if (enabled)
        RCC->APB1RSTR |= peripheral;
    else
        RCC->APB1RSTR &= ~peripheral;
}

void stm32f4_rccResetPeripheralAPB2(uint32_t peripheral, bool enabled)
{
    if (enabled)
        RCC->APB2RSTR |= peripheral;
    else
        RCC->APB2RSTR &= ~peripheral;
}

void stm32f4_rccGetClocksFrequencies(STM32F4_ClockFrequencies_t *clocks)
{
    // SYSCLK.
    uint32_t sysclk_source = RCC->CFGR & RCC_CFGR_SWS;
    switch (sysclk_source) {
    case RCC_SYSCLK_SOURCE_USED_HSI:
        clocks->sysclk_frequency_hz = HSI_VALUE;
        break;

    case RCC_SYSCLK_SOURCE_USED_HSE:
        clocks->sysclk_frequency_hz = HSE_VALUE;
        break;

    case RCC_SYSCLK_SOURCE_USED_PLLCLK: {
        uint32_t pll_source = (RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) >> 22;
        uint32_t pllm = RCC->PLLCFGR & RCC_PLLCFGR_PLLM;
        uint32_t pll_vco = 0;
        if (pll_source != RCC_PLL_SOURCE_HSI)
            pll_vco = (HSE_VALUE / pllm) * ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6);
        else
            pll_vco = (HSI_VALUE / pllm) * ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6);

        uint32_t pllp = (((RCC->PLLCFGR & RCC_PLLCFGR_PLLP) >> 16) + 1 ) * 2;
        clocks->sysclk_frequency_hz = pll_vco / pllp;
        break;
    }
    default:
        clocks->sysclk_frequency_hz = HSI_VALUE;
        break;
    }

    // HCLK.
    uint32_t hclk_prescaler_index = (RCC->CFGR & RCC_CFGR_HPRE) >> 4;
    uint32_t hclk_prescaler = stm32f4_APBAHB_prescaler_table[hclk_prescaler_index];
    clocks->hclk_frequency_hz = clocks->sysclk_frequency_hz >> hclk_prescaler;

    // PCLK1.
    uint32_t pclk1_prescaler_index = (RCC->CFGR & RCC_CFGR_PPRE1) >> 10;
    uint32_t pclk1_prescaler = stm32f4_APBAHB_prescaler_table[pclk1_prescaler_index];
    clocks->pclk1_frequency_hz = clocks->hclk_frequency_hz >> pclk1_prescaler;

    // PCLK2.
    uint32_t pclk2_prescaler_index = (RCC->CFGR & RCC_CFGR_PPRE2) >> 13;
    uint32_t pclk2_prescaler = stm32f4_APBAHB_prescaler_table[pclk2_prescaler_index];
    clocks->pclk2_frequency_hz = clocks->hclk_frequency_hz >> pclk2_prescaler;
}
