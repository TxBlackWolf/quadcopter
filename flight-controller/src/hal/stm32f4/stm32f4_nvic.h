//---------------------------------------------------------------------------------------------------------------
//
// Filename   : stm32f4_nvic.h
// Author     : Kuba Sejdak
// Created on : 25.10.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#ifndef STM32F4_NVIC_H
#define STM32F4_NVIC_H

#include <stdint.h>
#include <stdbool.h>

// IRQ config structure in NVIC.
typedef struct {
    uint8_t channel;
    uint8_t channel_preemption_priority;
    uint8_t channel_subpriority;
    bool enabled;
} IRQConfig_t;

void stm32f4_nvicInitIRQ(IRQConfig_t *config);

#endif
