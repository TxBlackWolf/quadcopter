#################################################################################################################
# CMAKE SETTINGS
#################################################################################################################

# Required cmake version.
cmake_minimum_required(VERSION 2.8.12)

# Project paths.
set(SKYVIPER_COMMON_PATH ${CMAKE_SOURCE_DIR}/common)
set(FLIGHTCONTROLLER_PATH ${CMAKE_SOURCE_DIR}/flight-controller)
set(FLIGHTCONTROLLER_SRC_PATH ${APP_PATH}/src)
set(FLIGHTCONTROLLER_BOARD_PATH ${FLIGHTCONTROLLER_SRC_PATH}/board)
set(FLIGHTCONTROLLER_DRIVERS_PATH ${FLIGHTCONTROLLER_SRC_PATH}/drivers)
set(FLIGHTCONTROLLER_HAL_PATH ${FLIGHTCONTROLLER_SRC_PATH}/hal)
set(FLIGHTCONTROLLER_UTILS_PATH ${FLIGHTCONTROLLER_SRC_PATH}/utils)

# Additional user defined macros.
include(${FLIGHTCONTROLLER_PATH}/cmake/drivers.cmake)
include(${FLIGHTCONTROLLER_PATH}/cmake/environment.cmake)
include(${FLIGHTCONTROLLER_PATH}/cmake/external_libs.cmake)
include(${FLIGHTCONTROLLER_PATH}/cmake/macros.cmake)

#################################################################################################################
# PROJECT SETTINGS
#################################################################################################################

if(NOT FLIGHTCONTROLLER_APP)
    set(FLIGHTCONTROLLER_APP "flight-controller")
endif()

if(NOT FLIGHTCONTROLLER_BOARD)
    set(FLIGHTCONTROLLER_BOARD "emulator_board")
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(PROJECT_NAME ${FLIGHTCONTROLLER_APP})
set(APP_NAME "flight-controller")
set(SUBAPP_NAME ${FLIGHTCONTROLLER_APP})
project(${PROJECT_NAME} C ASM)

#################################################################################################################
# TOOLCHAIN SETTINGS
#################################################################################################################

if(${FLIGHTCONTROLLER_BOARD} STREQUAL "emulator_board")
    set_toolchain("x86")
    set(FLIGHTCONTROLLER_HAL "emulator_hal")
elseif(${FLIGHTCONTROLLER_BOARD} STREQUAL "stm32f4_discovery")
    set_toolchain("arm")
    set(FLIGHTCONTROLLER_HAL "stm32f4")
endif()

# Set common build options.
set(EXECUTABLE_OUTPUT_PATH ${FLIGHTCONTROLLER_PATH}/bin/${FLIGHTCONTROLLER_BOARD}/${CMAKE_BUILD_TYPE})

# List project configuration.
message(STATUS "FlightController project configuration:")
message(STATUS "  Board: " ${FLIGHTCONTROLLER_BOARD})
message(STATUS "  Application: " ${SUBAPP_NAME})
message(STATUS "  Build type: " ${CMAKE_BUILD_TYPE})

#################################################################################################################
# OTHER SETTINGS
#################################################################################################################

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

configure_drivers()

include_directories(.)
#add_subdirectory(Common)
add_subdirectory(${APP_NAME})
