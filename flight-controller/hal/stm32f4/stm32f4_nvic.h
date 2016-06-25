////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       14.10.2015
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef STM32F4_NVIC_H
#define STM32F4_NVIC_H

#include <stdbool.h>
#include <stdint.h>

// IRQ config structure in NVIC.
typedef struct {
    uint8_t channel;
    uint8_t channel_preemption_priority;
    uint8_t channel_subpriority;
    bool enabled;
} IRQConfig_t;

void stm32f4_nvicInitIRQ(IRQConfig_t *config);

#endif
