set(SOURCES
    STM32Discovery.c
    UARTConsole.c
)

# Needed by Drivers.
include_directories(CMSIS)

set(MODULES
    CMSIS
    Drivers
)

RegisterComponent()