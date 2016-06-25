////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       22.07.2015
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "stm32f4_discovery.h"
#include "stm32f4_discovery_pinout.h"
#include "board/clock.h"
#include "board/console.h"
#include "hal/stm32f4/CMSIS/stm32f4xx.h"
#include "hal/stm32f4/stm32f4_gpio.h"
#include "hal/stm32f4/stm32f4_gpio_functions.h"
#include "hal/stm32f4/stm32f4_nvic.h"
#include "hal/stm32f4/stm32f4_pwm.h"
#include "hal/stm32f4/stm32f4_rcc.h"
#include "hal/stm32f4/stm32f4_timer.h"
#include "hal/timer.h"

#define COMMANDS_BAUD_RATE       115200

bool board_isEmergencyBoot()
{
    /// @todo Implement.
    return false;
}

bool board_isEmulator()
{
    return false;
}

void board_showSystemClocks()
{
    STM32F4_ClockFrequencies_t clocks;

    stm32f4_rccGetClocksFrequencies(&clocks);
    console_write("board: Available clocks:\n");
    console_write("board: sysclk          : %d kHz\n", clocks.sysclk_frequency_hz / 1000);
    console_write("board: hclk (AHB bus)  : %d kHz\n", clocks.hclk_frequency_hz / 1000);
    console_write("board: pclk1 (APB1 bus): %d kHz\n", clocks.pclk1_frequency_hz / 1000);
    console_write("board: pclk2 (APB2 bus): %d kHz\n", clocks.pclk2_frequency_hz / 1000);
}

bool board_periodicTimerInit(TimerHandle_t *timer_handle)
{
    timer_handle->device = PERIODIC_EVENT_TIMER;
    timer_handle->channel = PERIODIC_EVENT_TIMER_CHANNEL;

    // Configure timer.
    STM32F4_TimerConfig_t timer_config;
    timer_config.counter_mode = COUNTER_MODE_UP;
    timer_config.clock_division = CLOCK_DIVISION_1;
    timer_config.repetition_counter = 0;

    if (!stm32f4_timerSetPeriodConfig(timer_handle, (float) CLOCK_PERIODIC_TIMER_PERIOD_MS, &timer_config)) {
        console_write("board: Failed to set config for timer event frequency\n");
        return false;
    }

    if (!stm32f4_timerInit(timer_handle, &timer_config)) {
        console_write("board: Failed to initialize periodic timer\n");
        return false;
    }

    // Configure NVIC.
    IRQConfig_t nvic_config;
    nvic_config.channel = stm32f4_timerToIRQChannel(timer_handle, TIMER_IRQ_UPDATE);
    nvic_config.channel_preemption_priority = 0;
    nvic_config.channel_subpriority = 0;
    nvic_config.enabled = true;
    stm32f4_nvicInitIRQ(&nvic_config);

    timer_activate(timer_handle);
    return stm32f4_timerRegisterCallback(timer_handle, TIMER_IRQ_UPDATE, clock_processPeriodicEvents);
}

bool board_commandsInit(UARTHandle_t *uart_handle, HALEventCallback_t callback)
{
    uart_handle->device = COMMANDS_UART_DEVICE;
    uart_handle->gpio_tx.port = COMMANDS_GPIO_TX_PORT;
    uart_handle->gpio_tx.pin = COMMANDS_GPIO_TX_PIN;
    uart_handle->gpio_rx.port = COMMANDS_GPIO_RX_PORT;
    uart_handle->gpio_rx.pin = COMMANDS_GPIO_RX_PIN;

    // Configure GPIO TX and RX.
    STM32F4_GPIOConfig_t gpio_config;
    gpio_config.general_config.resistor_type = GPIO_RESISTOR_PULLUP;
    gpio_config.function = stm32f4_uartToPinFunction(uart_handle);
    gpio_config.speed = GPIO_SPEED_100MHz;
    gpio_config.mode = GPIO_MODE_ALTERNATE;
    gpio_config.output_type = GPIO_OUTPUT_PUSHPULL;

    gpio_config.general_config.direction = GPIO_DIRECTION_OUT;
    if (!stm32f4_gpioInit(&uart_handle->gpio_tx, &gpio_config))
        return false;

    gpio_config.general_config.direction = GPIO_DIRECTION_IN;
    if (!stm32f4_gpioInit(&uart_handle->gpio_rx, &gpio_config))
        return false;

    // Configure UART.
    STM32F4_UARTConfig_t uart_config;
    uart_config.general_config.protocol.baud_rate = COMMANDS_BAUD_RATE;
    uart_config.general_config.protocol.data_bits = UART_DATA_BITS_8;
    uart_config.general_config.protocol.stop_bits = UART_STOP_BITS_1;
    uart_config.general_config.protocol.parity = UART_PARTITY_NONE;
    uart_config.general_config.protocol.flow_control = UART_FLOW_CONTROL_NONE;
    uart_config.general_config.direction = UART_DIRECTION_BIDIRECTIONAL;
    uart_config.general_config.mode = UART_MODE_ASYNCHRONOUS;

    if (!stm32f4_uartInit(uart_handle, &uart_config))
        return false;

    // Configure NVIC.
    IRQConfig_t nvic_config;
    nvic_config.channel = stm32f4_uartToIRQChannel(uart_handle);
    nvic_config.channel_preemption_priority = 0;
    nvic_config.channel_subpriority = 0;
    nvic_config.enabled = true;
    stm32f4_nvicInitIRQ(&nvic_config);

    uart_activate(uart_handle);
    return stm32f4_uartRegisterCallback(uart_handle, UART_IRQ_RXNE_OVERRUN, callback);
}

bool board_engineInit(PWMHandle_t *pwm_handle, PWMConfig_t *pwm_config, GPIOConfig_t *gpio_general_config)
{
    // Configure GPIO.
    STM32F4_GPIOConfig_t gpio_config;
    gpio_config.general_config = *gpio_general_config;
    gpio_config.function = stm32f4_timerToPinFunction(&pwm_handle->timer);
    gpio_config.speed = GPIO_SPEED_100MHz;
    gpio_config.mode = GPIO_MODE_ALTERNATE;
    gpio_config.output_type = GPIO_OUTPUT_PUSHPULL;

    if (!stm32f4_gpioInit(&pwm_handle->gpio, &gpio_config)) {
        console_write("board: Failed to initialize GPIO for %s\n", pwm_handle->gpio.name);
        return false;
    }

    // Configure PWM.
    if (!stm32f4_pwmInit(pwm_handle, pwm_config)) {
        console_write("board: Failed to initialize PWM for %s\n", pwm_handle->gpio.name);
        return false;
    }

    return true;
}

bool board_strobeInit(GPIOHandle_t *gpio_handle, GPIOConfig_t *gpio_general_config)
{
    gpio_handle->port = LED_STROBE_PORT;
    gpio_handle->pin = LED_STROBE_PIN;
    gpio_handle->name = "led strobe";

    // Configure GPIO.
    STM32F4_GPIOConfig_t gpio_config;
    gpio_config.general_config = *gpio_general_config;
    gpio_config.function = GPIO_DIGITAL_PIN;
    gpio_config.speed = GPIO_SPEED_50MHz;
    gpio_config.mode = GPIO_MODE_OUT;
    gpio_config.output_type = GPIO_OUTPUT_PUSHPULL;

    if (!stm32f4_gpioInit(gpio_handle, &gpio_config)) {
        console_write("board: Failed to initialize GPIO for %s\n", gpio_handle->name);
        return false;
    }

    return true;
}
