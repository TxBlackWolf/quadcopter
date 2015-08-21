set(SOURCES
    gpio.c
    rcc.c
    uart.c
)

# Needed by Drivers.
include_directories(CMSIS)

RegisterModule()
