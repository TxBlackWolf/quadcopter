//---------------------------------------------------------------------------------------------------------------
//
// Filename   : stm32f4_rcc.c
// Author     : Kuba Sejdak
// Created on : 12.08.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#include "stm32f4_rcc.h"
#include "hal/rcc.h"

#if 0
void rcc_enablePeripheralClockAHB1(uint32_t peripheral, bool enabled)
{
    if(enabled)
        RCC->AHB1ENR |= peripheral;
    else
        RCC->AHB1ENR &= ~peripheral;
}

void rcc_resetPeripheralAHB1(uint32_t peripheral, bool enabled)
{
    if(enabled)
        RCC->AHB1RSTR |= peripheral;
    else
        RCC->AHB1RSTR &= ~peripheral;
}
#endif
