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

uint16_t command_getVersionMajor()
{
    for(int i = 0; ; ++i) {
        if(COMMAND_VERSION[i] == '.')
            return command_atoi(COMMAND_VERSION, i);
    }
}

uint16_t command_getVersionMinor()
{
    int dot_num = 0;
    int idx = 0;

    for(int i = 0; ; ++i) {
        if(COMMAND_VERSION[i] == '.') {
            if(++dot_num < 2) {
                idx = i + 1;
                continue;
            }

            return command_atoi(&COMMAND_VERSION[idx], i - idx);
        }
    }

    return 0;
}

uint16_t command_getVersionPatch()
{
    int idx = 0;

    for(int i = 0; ; ++i) {
        if(COMMAND_VERSION[i] == '.') {
            idx = i + 1;
            continue;
        }

        if(COMMAND_VERSION[i] != '\0')
            continue;

        return command_atoi(&COMMAND_VERSION[idx], i - idx);
    }

    return 0;
}

uint32_t command_computeCRC(const uint8_t *buffer __attribute__((unused)), uint32_t size __attribute__((unused)))
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

int command_atoi(char *str, int size)
{
    int k = 0;
    int n = size;
    char *p = str;

    while(n--) {
        k = (k << 3) + (k << 1) + (*p) - '0';
        ++p;
    }

    return k;
}
