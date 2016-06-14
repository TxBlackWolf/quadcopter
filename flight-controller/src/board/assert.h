////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       03.01.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef ASSERT_H
#define ASSERT_H

#include "console.h"

/// @brief Modified assert, that enters infinite loop after printing message to console.
#define board_assert(x)     if ((x) == 0) {                                                                      \
                                console_write("Assertion failed (%s:%d): '%s'\n", __FILE__, __LINE__, #x);      \
                                while (1);                                                                       \
                            }

#endif
