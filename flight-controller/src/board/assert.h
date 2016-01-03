//---------------------------------------------------------------------------------------------------------------
//
// Filename   : assert.h
// Author     : Kuba Sejdak
// Created on : 03.01.2016
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#ifndef ASSERT_H
#define ASSERT_H

#include "console.h"

#define board_assert(x)     if((x) == 0) {                                                                      \
                                console_write("Assertion failed (%s:%d): '%s'\n", __FILE__, __LINE__, #x);      \
                                while(1);                                                                       \
                            }

#endif
