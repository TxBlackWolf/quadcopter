////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       24.04.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef COMMAND_STATISTICS_H
#define COMMAND_STATISTICS_H

void commandStatistics_markReceived();
void commandStatistics_markBroken();
void commandStatistics_markLost(int n);

#endif
