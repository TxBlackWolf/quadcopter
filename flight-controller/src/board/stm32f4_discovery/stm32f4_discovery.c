 //---------------------------------------------------------------------------------------------------------------
//
// Filename   : stm32f4_discovery.c
// Author     : Kuba Sejdak
// Created on : 22.07.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#include "board/board.h"
#include "stm32f4_discovery.h"

bool board_init()
{
    // TODO: implement.
    return false;
}

void board_strobeInit(GPIOConfig_t *config)
{
    config->port = GPIO_PORT_A;
    config->pin = GPIO_PIN_5;
}
