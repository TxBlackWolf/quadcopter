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
    return true;
}
