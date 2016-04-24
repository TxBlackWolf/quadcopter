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

static uint32_t command_nextId = 0;
static uint32_t command_receivedCount = 0;
static uint32_t command_lostCount = 0;
static uint32_t command_brokenCount = 0;