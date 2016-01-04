//---------------------------------------------------------------------------------------------------------------
//
// Filename   : emulated_engine.c
// Author     : Kuba Sejdak
// Created on : 04.01.2016
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#include "emulated_engine.h"
#include "drivers/engines/engine.h"

bool engines_init()
{
    return true;
}

void engines_enable_one(PWMHandle_t *engine)
{
    // TODO: implement.
}

void engines_disable_one(PWMHandle_t *engine)
{
    // TODO: implement.
}

void engines_enable_all()
{
    // TODO: implement.
}

void engines_disable_all()
{
    // TODO: implement.
}

void engines_setThrottle(PWMHandle_t *engine, uint32_t throttle_perc)
{
    // TODO: implement.
}
