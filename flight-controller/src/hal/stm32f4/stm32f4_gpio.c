//---------------------------------------------------------------------------------------------------------------
//
// Filename   : stm32f4_gpio.c
// Author     : Kuba Sejdak
// Created on : 11.08.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#include "stm32f4_gpio.h"
#include "stm32f4_gpio_functions.h"
#include "hal/gpio.h"
#include "hal/rcc.h"
#include "CMSIS/stm32f4xx.h"

typedef GPIO_TypeDef GPIO_t;

//---------------------------------------------------------------------------------------------------------------
// HELPER FUNCTIONS
//---------------------------------------------------------------------------------------------------------------

GPIO_t *gpio_getRegisters(GPIOPort_t port)
{
    switch(port)
    {
    case STM32F4_GPIO_PORT_A:   return GPIOA;
    case STM32F4_GPIO_PORT_B:   return GPIOB;
    case STM32F4_GPIO_PORT_C:   return GPIOC;
    case STM32F4_GPIO_PORT_D:   return GPIOD;
    case STM32F4_GPIO_PORT_E:   return GPIOE;
    case STM32F4_GPIO_PORT_F:   return GPIOF;
    case STM32F4_GPIO_PORT_G:   return GPIOG;
    case STM32F4_GPIO_PORT_H:   return GPIOH;
    case STM32F4_GPIO_PORT_I:   return GPIOI;
    }

    return 0;
}

uint32_t gpio_getPinMask(GPIOPin_t pin)
{
    return (1 << pin);
}

void gpio_setPinFunction(GPIOPort_t port, GPIOPin_t pin, uint8_t function)
{
    GPIO_t *gpio = gpio_getRegisters(port);
    uint32_t value = (function << (pin & 0x7) * 4);
    uint32_t afr_half = pin >> 3;
    gpio->AFR[afr_half] |= value;
}

void stm32f4_gpioEnableClock(GPIOHandle_t handle, bool value)
{
    uint32_t ahb1_peripheral = 0;
    switch(handle.port)
    {
    case STM32F4_GPIO_PORT_A:   ahb1_peripheral = RCC_AHB1_PERIPHERAL_GPIOA; break;
    case STM32F4_GPIO_PORT_B:   ahb1_peripheral = RCC_AHB1_PERIPHERAL_GPIOB; break;
    case STM32F4_GPIO_PORT_C:   ahb1_peripheral = RCC_AHB1_PERIPHERAL_GPIOC; break;
    case STM32F4_GPIO_PORT_D:   ahb1_peripheral = RCC_AHB1_PERIPHERAL_GPIOD; break;
    case STM32F4_GPIO_PORT_E:   ahb1_peripheral = RCC_AHB1_PERIPHERAL_GPIOE; break;
    case STM32F4_GPIO_PORT_F:   ahb1_peripheral = RCC_AHB1_PERIPHERAL_GPIOF; break;
    case STM32F4_GPIO_PORT_G:   ahb1_peripheral = RCC_AHB1_PERIPHERAL_GPIOG; break;
    case STM32F4_GPIO_PORT_H:   ahb1_peripheral = RCC_AHB1_PERIPHERAL_GPIOH; break;
    case STM32F4_GPIO_PORT_I:   ahb1_peripheral = RCC_AHB1_PERIPHERAL_GPIOI; break;
    }

    rcc_enablePeripheralClockAHB1(ahb1_peripheral, value);
}

//---------------------------------------------------------------------------------------------------------------
// INTERFACE FUNCTIONS
//---------------------------------------------------------------------------------------------------------------

GPIOHandle_t stm32f4_gpioInit(GPIOPort_t port, GPIOPort_t pin, STM32F4_GPIOConfig_t config)
{
    GPIOHandle_t handle;
    handle.port = port;
    handle.pin = pin;

    // Enable clock for pin.
    gpio_activate(handle);

    // Set pin alternate function if set
    if(config.function != GPIO_DIGITAL_PIN)
        gpio_setPinFunction(port, pin, config.function);

    GPIO_t *gpio = gpio_getRegisters(port);

    // Set mode.
    gpio->MODER |= (config.mode << (pin * 2));

    if(config.mode == GPIO_MODE_OUT || config.mode == GPIO_MODE_ALTERNATE)
    {
        // Set speed.
        gpio->OSPEEDR |= (config.speed << (pin * 2));

        // Set output mode.
        gpio->OTYPER |= (config.output_type << pin);
    }

    // Set pullup/pulldown resistor.
    gpio->PUPDR |= (config.general_config.resistor_type << (pin * 2));

    return handle;
}

void gpio_activate(GPIOHandle_t handle)
{
    stm32f4_gpioEnableClock(handle, true);
}

void gpio_deactivate(GPIOHandle_t handle)
{
    stm32f4_gpioEnableClock(handle, true);
}

bool gpio_readPin(GPIOHandle_t handle)
{
    GPIO_t *gpio = gpio_getRegisters(handle.port);
    uint16_t pin_mask = gpio_getPinMask(handle.pin);
    return (gpio->IDR & pin_mask);
}

uint16_t gpio_readPort(GPIOPort_t port)
{
    GPIO_t *gpio = gpio_getRegisters(port);
    return gpio->IDR;
}

bool gpio_writePin(GPIOHandle_t handle, bool value)
{
    GPIO_t *gpio = gpio_getRegisters(handle.port);
    uint16_t pin_mask = gpio_getPinMask(handle.pin);
    if(value)
        gpio->ODR |= pin_mask;
    else
        gpio->ODR &= ~pin_mask;

    return (gpio->ODR & pin_mask);
}

bool gpio_writePort(GPIOPort_t port, uint16_t value)
{
    GPIO_t *gpio = gpio_getRegisters(port);
    gpio->ODR = value;

    return (gpio->ODR == value);
}

void gpio_pinConfigLock(GPIOHandle_t handle)
{
    GPIO_t *gpio = gpio_getRegisters(handle.port);
    volatile uint32_t value = (1 << 16);

    value |= handle.pin;
    gpio->LCKR = value;
    gpio->LCKR = handle.pin;
    gpio->LCKR = value;
    value = gpio->LCKR;
    value = gpio->LCKR;
}
