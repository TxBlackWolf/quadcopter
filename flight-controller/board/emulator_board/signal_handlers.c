////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       06.01.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "signal_handlers.h"
#include "hal/timer.h"
#include "hal/emulator_hal/linux_timer.h"

#include <assert.h>

void sigalrm_handler(int sig_num, siginfo_t *sig_info, void *unused __attribute__((unused)))
{
    assert(sig_num == SIGALRM);

    TimerHandle_t *timer_handle = (TimerHandle_t *) sig_info->si_value.sival_ptr;
    Emulator_TimerPrivateData_t *private_data = (Emulator_TimerPrivateData_t *) timer_handle->private_data;
    assert(private_data);
    if(private_data->enabled) {
        assert(private_data->callback);
        private_data->callback();
    }
}
