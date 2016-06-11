set(SOURCES
    barometer.h
)

add_subdirectory(${FLIGHTCONTROLLER_BAROMETER_DEVICE})
message(STATUS "Enabling barometer: ${FLIGHTCONTROLLER_BAROMETER_DEVICE}")

register_module()
