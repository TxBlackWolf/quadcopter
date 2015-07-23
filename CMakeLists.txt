#################################################################################################################
# CMAKE SETTINGS
#################################################################################################################

# required cmake version
cmake_minimum_required(VERSION 2.8.12)

# project paths
set(SKYVIPER_COMMON_PATH ${CMAKE_SOURCE_DIR}/Common)
set(FLIGHTCONTROLLER_PATH ${CMAKE_SOURCE_DIR}/FlightController)
set(FLIGHTCONTROLLER_SRC_PATH ${FLIGHTCONTROLLER_PATH}/src)

# additional user defined macros
include(${FLIGHTCONTROLLER_PATH}/cmake/CMakeMacros.cmake)
include(${FLIGHTCONTROLLER_PATH}/cmake/CMakeHAL.cmake)
include(${FLIGHTCONTROLLER_PATH}/cmake/CMakeExternalLibs.cmake)

#################################################################################################################
# PROJECT SETTINGS
#################################################################################################################

# project name
set(PROJECT_NAME FlightController)
set(APP_NAME FlightController)
set(APP_TARGET_NAME FlightController)
project(${PROJECT_NAME})

if(NOT FLIGHTCONTROLER_ARCH_TYPE)
    set(FLIGHTCONTROLER_ARCH_TYPE "x86")
endif()

if(NOT FLIGHTCONTROLER_PLATFORM_TYPE)
    set(FLIGHTCONTROLER_PLATFORM_TYPE "Emulator")
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# set binary output path
set(EXECUTABLE_OUTPUT_PATH ${FLIGHTCONTROLLER_PATH}/bin/${FLIGHTCONTROLER_ARCH_TYPE}/${FLIGHTCONTROLER_PLATFORM_TYPE}/${CMAKE_BUILD_TYPE})

# list project configuration
message(STATUS "FlightController project configuration:")
message(STATUS "  Platform type: " ${FLIGHTCONTROLER_PLATFORM_TYPE})
message(STATUS "  Architecture type: " ${FLIGHTCONTROLER_ARCH_TYPE})
message(STATUS "  Project build type: " ${CMAKE_BUILD_TYPE})

#################################################################################################################
# TOOLCHAIN SETTINGS
#################################################################################################################

if(${FLIGHTCONTROLER_ARCH_TYPE} STREQUAL "x86")
    set(CMAKE_C_COMPILER "gcc")
    set(CMAKE_C_FLAGS "-Wall -Wextra")
    set(CMAKE_C_FLAGS_DEBUG "-O0")
    set(CMAKE_C_FLAGS_RELEASE "-O2 -Werror")
elseif(${FLIGHTCONTROLER_ARCH_TYPE} STREQUAL "arm")
    set(CMAKE_C_COMPILER "arm-linux-gnueabihf-gcc")
    set(CMAKE_C_FLAGS "-Wall -Wextra")
    set(CMAKE_C_FLAGS_DEBUG "-O0")
    set(CMAKE_C_FLAGS_RELEASE "-O2 -Werror")
endif()

message(STATUS "Setting toolchain to:")
message(STATUS "  compiler: " ${CMAKE_C_COMPILER})
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    message(STATUS "  compiler flags: ${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_DEBUG}")
else()
    message(STATUS "  compiler flags: ${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_RELEASE}")
endif()

# options passed to the compiler
add_definitions(-std=c11)

#FindExternalLibs()

#################################################################################################################
# OTHER SETTINGS
#################################################################################################################

# turn on solution folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# configure HAL
ConfigureHal()

# source and include paths
include_directories(.)
#add_subdirectory(Common)
add_subdirectory(FlightController)
