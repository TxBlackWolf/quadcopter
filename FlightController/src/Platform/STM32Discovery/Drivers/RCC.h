//---------------------------------------------------------------------------------------------------------------
//
// Filename   : RCC.h
// Author     : Kuba Sejdak
// Created on : 12.08.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#ifndef RCC_H
#define RCC_H

#include "Platform/STM32Discovery/CMSIS/stm32f4xx.h"

#include <stdint.h>
#include <stdbool.h>

typedef RCC_TypeDef RCC_t;

// AHB1 peripherals.
#define RCC_AHB1_PERIPHERAL_GPIOA           ((uint32_t) 0x00000001)
#define RCC_AHB1_PERIPHERAL_GPIOB           ((uint32_t) 0x00000002)
#define RCC_AHB1_PERIPHERAL_GPIOC           ((uint32_t) 0x00000004)
#define RCC_AHB1_PERIPHERAL_GPIOD           ((uint32_t) 0x00000008)
#define RCC_AHB1_PERIPHERAL_GPIOE           ((uint32_t) 0x00000010)
#define RCC_AHB1_PERIPHERAL_GPIOF           ((uint32_t) 0x00000020)
#define RCC_AHB1_PERIPHERAL_GPIOG           ((uint32_t) 0x00000040)
#define RCC_AHB1_PERIPHERAL_GPIOH           ((uint32_t) 0x00000080)
#define RCC_AHB1_PERIPHERAL_GPIOI           ((uint32_t) 0x00000100)
#define RCC_AHB1_PERIPHERAL_CRC             ((uint32_t) 0x00001000)
#define RCC_AHB1_PERIPHERAL_FLITF           ((uint32_t) 0x00008000)
#define RCC_AHB1_PERIPHERAL_SRAM1           ((uint32_t) 0x00010000)
#define RCC_AHB1_PERIPHERAL_SRAM2           ((uint32_t) 0x00020000)
#define RCC_AHB1_PERIPHERAL_BKPSRAM         ((uint32_t) 0x00040000)
#define RCC_AHB1_PERIPHERAL_CCMDATARAMEN    ((uint32_t) 0x00100000)
#define RCC_AHB1_PERIPHERAL_DMA1            ((uint32_t) 0x00200000)
#define RCC_AHB1_PERIPHERAL_DMA2            ((uint32_t) 0x00400000)
#define RCC_AHB1_PERIPHERAL_ETH_MAC         ((uint32_t) 0x02000000)
#define RCC_AHB1_PERIPHERAL_ETH_MAC_Tx      ((uint32_t) 0x04000000)
#define RCC_AHB1_PERIPHERAL_ETH_MAC_Rx      ((uint32_t) 0x08000000)
#define RCC_AHB1_PERIPHERAL_ETH_MAC_PTP     ((uint32_t) 0x10000000)
#define RCC_AHB1_PERIPHERAL_OTG_HS          ((uint32_t) 0x20000000)
#define RCC_AHB1_PERIPHERAL_OTG_HS_ULPI     ((uint32_t) 0x40000000)

void RCCEnablePeripheralClockAHB1(uint32_t peripheral, bool enabled);
void RCCResetPeripheralAHB1(uint32_t peripheral, bool enabled);

#endif
