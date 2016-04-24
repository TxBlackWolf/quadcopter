////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       15.01.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "command_common.h"

#include <stdio.h>

SynchronizationFunctor critical_section = NULL;
CRCFunctor crc_functor = NULL;

void command_registerSynchronizationFunctor(SynchronizationFunctor functor)
{
    critical_section = functor;
}

void command_registerCRCFunctor(CRCFunctor functor)
{
    crc_functor = functor;
}

void command_enterCriticalSection()
{
    critical_section(true);
}

void command_leaveCriticalSection()
{
    critical_section(false);
}

uint32_t command_computeCRC(const uint8_t *buffer, uint32_t size)
{
    /// @todo Implement.
    return 0;
}

void command_copyBuffer(uint8_t *to, const uint8_t *from, int size)
{
    for(int i = 0; i < size; ++i)
        to[i] = from[i];
}

void command_shiftBuffer(uint8_t *buffer, int size, int positions)
{
    command_copyBuffer(buffer, buffer + positions, size - positions);
}
