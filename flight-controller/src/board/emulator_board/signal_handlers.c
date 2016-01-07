//---------------------------------------------------------------------------------------------------------------
//
// Filename   : signal_handlers.c
// Author     : Kuba Sejdak
// Created on : 06.01.2016
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#include "signal_handlers.h"
#include "board/clock.h"

#include <signal.h>

void signal_handler(int sig_num)
{
    switch(sig_num) {
    case SIGALRM:
        clock_processPeriodicEvents();
        break;
    }
}
