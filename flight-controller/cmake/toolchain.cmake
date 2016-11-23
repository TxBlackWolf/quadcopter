macro(set_toolchain ARCH)
    if (${ARCH} STREQUAL "x86")
        # Set toolchain for target.
        set(CMAKE_C_COMPILER "x86_64-linux-gnu-gcc")
        set(CMAKE_ASM_COMPILER "x86_64-linux-gnu-as")
        set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS})

        # Set compilation flags.
        set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-std=gnu11 -Wall -Wextra")
        set(CMAKE_C_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG} "-O0")
        set(CMAKE_C_FLAGS_RELEASE ${CMAKE_C_FLAGS_RELEASE} "-O2 -Werror")

    elseif (${ARCH} STREQUAL "arm")
        # Set toolchain for target.
        set(CMAKE_C_COMPILER "arm-none-eabi-gcc")
        set(CMAKE_ASM_COMPILER "arm-none-eabi-as")
        set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-mcpu=cortex-m4 -march=armv7e-m -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fno-common -ffunction-sections -fdata-sections -nostdlib -static -lc -lgcc")
        set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS)
        set(CMAKE_EXECUTABLE_SUFFIX ".elf")

        # Set linker script.
        set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-T ${FLIGHTCONTROLLER_PATH}/board/${FLIGHTCONTROLLER_BOARD}/${FLIGHTCONTROLLER_BOARD}.ld")
        set(CMAKE_EXE_LINKER_FLAGS_RELEASE ${CMAKE_EXE_LINKER_FLAGS_RELEASE} "-s")

        # Set compilation flags.
        set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-std=c11 -Wall -Wextra")
        set(CMAKE_C_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG} "-O0")
        set(CMAKE_C_FLAGS_RELEASE ${CMAKE_C_FLAGS_RELEASE} "-O2 -Werror")

    endif ()

    string(REGEX REPLACE ";" " " CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
    string(REGEX REPLACE ";" " " CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}")
    string(REGEX REPLACE ";" " " CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")
    string(REGEX REPLACE ";" " " CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")
    string(REGEX REPLACE ";" " " CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE}")

    message(STATUS "Setting toolchain to:")
    message(STATUS "  compiler: " ${CMAKE_C_COMPILER})
    message(STATUS "  assembler: " ${CMAKE_ASM_COMPILER})
    if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        message(STATUS "  compiler flags: ${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_DEBUG}")
    else()
        message(STATUS "  compiler flags: ${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_RELEASE}")
    endif ()
endmacro()
