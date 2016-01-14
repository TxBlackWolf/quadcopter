//=============================================================================================
//
// Filename   : signal_handlers.h
// Author     : Kuba Sejdak
// Created on : 06.01.2016
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//=============================================================================================

#ifndef SIGNAL_HANDLERS_H
#define SIGNAL_HANDLERS_H

#include <signal.h>

void sigalrm_handler(int sig_num, siginfo_t *sig_info, void *unused);

#endif
