////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       10.04.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CONTROLLER_H
#define CONTROLLER_H

/// @brief Starts controller main loop.
/// @note This function should return its value directly to main() exit point.
/// @return O on success, otherwise values greater than 0.
int controller_run();

#endif
