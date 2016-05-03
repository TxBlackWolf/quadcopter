////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       24.04.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "command_statistics.h"

#include <stdint.h>

static uint32_t commandStatistics_receivedCount = 0;
static uint32_t commandStatistics_brokenCount = 0;
static uint32_t commandStatistics_lostCount = 0;

void commandStatistics_markReceived()
{
    ++commandStatistics_receivedCount;
}

void commandStatistics_markBroken()
{
    ++commandStatistics_brokenCount;
}

void commandStatistics_markLost(int n)
{
    commandStatistics_lostCount += n;
}
