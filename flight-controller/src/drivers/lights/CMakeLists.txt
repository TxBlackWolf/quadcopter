set(SOURCES
    lights.h
)

add_subdirectory(${FLIGHTCONTROLLER_LIGHTS_DEVICE})
message(STATUS "Enabling lights: ${FLIGHTCONTROLLER_LIGHTS_DEVICE}")

register_module()

link_target(${FLIGHTCONTROLLER_BOARD_PATH})
