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

typedef struct {
  uint8_t channel;                          /*!< Specifies the IRQ channel to be enabled or disabled.
                                            This parameter can be an enumerator of @ref IRQn_Type
                                            enumeration (For the complete STM32 Devices IRQ Channels
                                            list, please refer to stm32f4xx.h file) */

  uint8_t channel_preemption_priority;      /*!< Specifies the pre-emption priority for the IRQ channel
                                            specified in NVIC_IRQChannel. This parameter can be a value
                                            between 0 and 15 as described in the table @ref MISC_NVIC_Priority_Table
                                            A lower priority value indicates a higher priority */

  uint8_t channel_subpriority;              /*!< Specifies the subpriority level for the IRQ channel specified
                                            in NVIC_IRQChannel. This parameter can be a value
                                            between 0 and 15 as described in the table @ref MISC_NVIC_Priority_Table
                                            A lower priority value indicates a higher priority */

  bool enabled;                             /*!< Specifies whether the IRQ channel defined in NVIC_IRQChannel
                                            will be enabled or disabled.
                                            This parameter can be set either to ENABLE or DISABLE */
} IRQConfig_t;

#endif
