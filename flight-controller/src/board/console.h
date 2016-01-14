//=============================================================================================
//
// Filename   : console.h
// Author     : Kuba Sejdak
// Created on : 22.07.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//=============================================================================================

#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdbool.h>

bool console_init();
int console_write(const char *format, ...);

#endif
