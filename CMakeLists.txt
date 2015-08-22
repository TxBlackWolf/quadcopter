#################################################################################################################
# CMAKE SETTINGS
#################################################################################################################

# Required cmake version.
cmake_minimum_required(VERSION 2.8.12)

# Project paths.
set(SKYVIPER_COMMON_PATH ${CMAKE_SOURCE_DIR}/common)
set(FLIGHTCONTROLLER_PATH ${CMAKE_SOURCE_DIR}/flight-controller)
set(FLIGHTCONTROLLER_SRC_PATH ${APP_PATH}/src)
set(FLIGHTCONTROLLER_DRIVERS_PATH ${FLIGHTCONTROLLER_SRC_PATH}/drivers)

# Additional user defined macros.
include(${FLIGHTCONTROLLER_PATH}/cmake/drivers.cmake)
include(${FLIGHTCONTROLLER_PATH}/cmake/environment.cmake)
include(${FLIGHTCONTROLLER_PATH}/cmake/external_libs.cmake)
include(${FLIGHTCONTROLLER_PATH}/cmake/macros.cmake)

#################################################################################################################
# PROJECT SETTINGS
#################################################################################################################

set(PROJECT_NAME flight-controller)
set(APP_NAME flight-controller)
project(${PROJECT_NAME} C ASM)

if(NOT FLIGHTCONTROLLER_BOARD)
    set(FLIGHTCONTROLLER_BOARD "emulator")
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

#################################################################################################################
# TOOLCHAIN SETTINGS
#################################################################################################################

if(${FLIGHTCONTROLLER_BOARD} STREQUAL "emulator")
    set_toolchain("x86")
    set(FLIGHTCONTROLLER_HAL "emulator")
elseif(${FLIGHTCONTROLLER_BOARD} STREQUAL "stm32f4_discovery")
    set_toolchain("arm")
    set(FLIGHTCONTROLLER_HAL "stm32f4")
endif()

# Set common build options.
set(EXECUTABLE_OUTPUT_PATH ${FLIGHTCONTROLLER_PATH}/bin/${FLIGHTCONTROLLER_BOARD}/${CMAKE_BUILD_TYPE})

# List project configuration.
message(STATUS "FlightController project configuration:")
message(STATUS "  Board: " ${FLIGHTCONTROLLER_BOARD})
message(STATUS "  Build type: " ${CMAKE_BUILD_TYPE})

#################################################################################################################
# OTHER SETTINGS
#################################################################################################################

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

configure_drivers()

include_directories(.)
#add_subdirectory(Common)
add_subdirectory(${APP_NAME})
