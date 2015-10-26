//---------------------------------------------------------------------------------------------------------------
//
// Filename   : stm32f4_nvic.c
// Author     : Kuba Sejdak
// Created on : 25.10.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#include "stm32f4_nvic.h"
#include "CMSIS/stm32f4xx.h"

//---------------------------------------------------------------------------------------------------------------
// HELPER FUNCTIONS
//---------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------
// INTERFACE FUNCTIONS
//---------------------------------------------------------------------------------------------------------------

void stm32f4_nvicInitIRQ(IRQConfig_t *config)
{
    uint8_t tmppriority = 0x00, tmppre = 0x00, tmpsub = 0x0F;

    if(!config->enabled) {
        NVIC->ICER[config->channel >> 5] = 1 << (config->channel & 0x1f);
        return;
    }

    /* Compute the Corresponding IRQ Priority --------------------------------*/
    tmppriority = (0x700 - ((SCB->AIRCR) & (uint32_t)0x700)) >> 8;
    tmppre = (0x4 - tmppriority);
    tmpsub = tmpsub >> tmppriority;

    tmppriority = config->channel_preemption_priority << tmppre;
    tmppriority |= (uint8_t)(config->channel_subpriority & tmpsub);

    tmppriority = tmppriority << 0x04;

    NVIC->IP[config->channel] = tmppriority;

    // Enable selected IRQ channel.
    NVIC->ISER[config->channel >> 5] = 1 << (config->channel & 0x1f);
}
