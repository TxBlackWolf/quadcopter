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
#include <stdio.h>

static uint32_t commandStatistics_receivedCount = 0;
static uint32_t commandStatistics_brokenCount = 0;
static uint32_t commandStatistics_lostCount = 0;

void commandStatistics_markReceived()
{
    ++commandStatistics_receivedCount;
    printf("receive: %d\n", commandStatistics_receivedCount);
    fflush(stdout);
}

void commandStatistics_markBroken()
{
    ++commandStatistics_brokenCount;
    printf("broken: %d\n", commandStatistics_brokenCount);
    fflush(stdout);
}

void commandStatistics_markLost(int n)
{
    commandStatistics_lostCount += n;
    printf("lost: %d\n", commandStatistics_lostCount);
    fflush(stdout);
}
