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

//---------------------------------------------------------------------------------------------------------------
// INTERFACE FUNCTIONS
//---------------------------------------------------------------------------------------------------------------

void gpio_setPinFunction(GPIOPort_t port, GPIOPin_t pin, uint8_t function)
{
    GPIO_t *gpio = gpio_getRegisters(port);
    uint32_t value = (function << (pin & 0x7) * 4);
    uint32_t afr_half = pin >> 3;
    gpio->AFR[afr_half] |= value;
}

GPIOHandle_t stm32f4_gpioInit(GPIOPort_t port, GPIOPort_t pin, STM32F4_GPIOConfig_t config)
{
    // Set pin alternate function.
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

    GPIOHandle_t handle;
    handle.port = port;
    handle.pin = pin;
    return handle;
}

void gpio_deactivate(GPIOHandle_t handle)
{
    /*
    uint32_t port_clock = 0;
    switch(handle.port)
    {
    case STM32F4_GPIO_PORT_A:   port_clock = RCC_AHB1_PERIPHERAL_GPIOA; break;
    case STM32F4_GPIO_PORT_B:   port_clock = RCC_AHB1_PERIPHERAL_GPIOB; break;
    case STM32F4_GPIO_PORT_C:   port_clock = RCC_AHB1_PERIPHERAL_GPIOC; break;
    case STM32F4_GPIO_PORT_D:   port_clock = RCC_AHB1_PERIPHERAL_GPIOD; break;
    case STM32F4_GPIO_PORT_E:   port_clock = RCC_AHB1_PERIPHERAL_GPIOE; break;
    case STM32F4_GPIO_PORT_F:   port_clock = RCC_AHB1_PERIPHERAL_GPIOF; break;
    case STM32F4_GPIO_PORT_G:   port_clock = RCC_AHB1_PERIPHERAL_GPIOG; break;
    case STM32F4_GPIO_PORT_H:   port_clock = RCC_AHB1_PERIPHERAL_GPIOH; break;
    case STM32F4_GPIO_PORT_I:   port_clock = RCC_AHB1_PERIPHERAL_GPIOI; break;
    }

    rcc_resetPeripheralAHB1(port_clock, false);
    */
}

bool gpio_readPin(GPIOHandle_t handle)
{
    GPIO_t *gpio = gpio_getRegisters(handle.port);
    return (gpio->IDR & handle.pin);
}

uint16_t gpio_readPort(GPIOPort_t port)
{
    GPIO_t *gpio = gpio_getRegisters(port);
    return gpio->IDR;
}

bool gpio_writePin(GPIOHandle_t handle, bool value)
{
    GPIO_t *gpio = gpio_getRegisters(handle.port);
    if(value)
        gpio->ODR |= handle.pin;
    else
        gpio->ODR &= ~handle.pin;

    return (gpio->ODR & handle.pin);
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
