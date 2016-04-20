//=============================================================================================
//
// Filename   : emulator_board.c
// Author     : Kuba Sejdak
// Created on : 04.01.2016
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//=============================================================================================

#include "emulator_board.h"
#include "signal_handlers.h"
#include "board/clock.h"
#include "board/console.h"
#include "board/board_pinout.h"
#include "hal/emulator_hal/emulator_gpio.h"
#include "hal/emulator_hal/linux_timer.h"
#include "hal/emulator_hal/network_uart.h"

#include <signal.h>
#include <string.h>

bool board_isEmergencyBoot()
{
    /// @todo Implement.
    return false;
}

bool board_isEmulator()
{
    return true;
}

void board_showSystemClocks()
{
    // Empty.
}

bool board_periodicTimerInit(TimerHandle_t *timer_handle)
{
    Emulator_TimerConfig_t timer_config;
    timer_config.signal_handler = sigalrm_handler;
    timer_config.sig_num = SIGALRM;
    timer_config.period_ms = CLOCK_PERIODIC_TIMER_PERIOD_MS;

    if(!emulator_timerInit(timer_handle, &timer_config)) {
        console_write("board: Failed to initialize emulator timer for periodic timer\n");
        return false;
    }

    LinuxTimerPrivateData_t *private_data = (LinuxTimerPrivateData_t *) timer_handle->private_data;
    private_data->callback = clock_processPeriodicEvents;

    timer_activate(timer_handle);
    return true;
}

bool board_commandsInit(UARTHandle_t *uart_handle)
{
    Emulator_UARTConfig_t uart_config;
    strcpy((char *) uart_config.ip, NETWORK_COMMANDS_IP);
    uart_config.port = NETWORK_COMMANDS_PORT;
    uart_config.protocol = NETWORK_COMMANDS_PROTOCOL;

    bool status = emulator_uartInit(uart_handle, &uart_config);
    if(status)
        uart_activate(uart_handle);

    return status;
}

bool board_strobeInit(GPIOHandle_t *gpio_handle, GPIOConfig_t *gpio_general_config __attribute__((unused)))
{
    return emulator_gpioInit(gpio_handle);
}

bool board_engineInit(PWMHandle_t *pwm_handle __attribute__((unused)), PWMConfig_t *pwm_config __attribute__((unused)), GPIOConfig_t *gpio_general_config __attribute__((unused)))
{
    /// @todo Implement.
    return true;
}
