////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       25.10.2015
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "stm32f4_nvic.h"
#include "CMSIS/stm32f4xx.h"

//=============================================================================================
// INTERFACE FUNCTIONS
//=============================================================================================

void stm32f4_nvicInitIRQ(IRQConfig_t *config)
{
    if(!config->enabled) {
        NVIC->ICER[config->channel >> 5] = 1 << (config->channel & 0x1f);
        return;
    }

    // Compute corresponding IRQ priority.
    uint8_t priority = (0x700 - (SCB->AIRCR & 0x700)) >> 8;
    uint8_t group_prio_shift = 0x4 - priority;
    uint8_t sub_prio_mask = 0xf >> priority;

    priority = config->channel_preemption_priority << group_prio_shift;
    priority |= config->channel_subpriority & sub_prio_mask;
    priority <<= 4;
    NVIC->IP[config->channel] = priority;

    // Enable selected IRQ channel.
    NVIC->ISER[config->channel >> 5] = 1 << (config->channel & 0x1f);
}
