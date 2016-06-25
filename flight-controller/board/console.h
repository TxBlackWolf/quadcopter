////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       22.07.2015
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdbool.h>

/// @brief Initializes console. Depending on board implementation it could be serial, ethernet etc.
/// @return True on success, false otherwise.
bool console_init();

/// @brief Writes formatted string to console.
/// @param [in] format              Formatted string. May include printf-like modifiers.
void console_write(const char *format, ...);

#endif
