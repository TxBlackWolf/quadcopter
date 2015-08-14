//---------------------------------------------------------------------------------------------------------------
//
// Filename   : RCC.c
// Author     : Kuba Sejdak
// Created on : 12.08.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#include "RCC.h"

void RCCEnablePeripheralClockAHB1(uint32_t peripheral, bool enabled)
{
    if(enabled)
        RCC->AHB1ENR |= peripheral;
    else
        RCC->AHB1ENR &= ~peripheral;
}

void RCCResetPeripheralAHB1(uint32_t peripheral, bool enabled)
{
    if(enabled)
        RCC->AHB1RSTR |= peripheral;
    else
        RCC->AHB1RSTR &= ~peripheral;
}
