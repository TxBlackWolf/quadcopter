set(SOURCES
    lights.h
)

if(${FLIGHTCONTROLLER_USE_LIGHTS})
    add_subdirectory(${FLIGHTCONTROLLER_LIGHTS_DEVICE})
    message(STATUS "Enabling lights: ${FLIGHTCONTROLLER_LIGHTS_DEVICE}")
else()
    message(STATUS "Lights disabled")
endif()

register_module()

link_target(${FLIGHTCONTROLLER_BOARD_PATH})
