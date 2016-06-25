set(SOURCES
    magnetometer.h
)

add_subdirectory(${FLIGHTCONTROLLER_MAGNETOMETER_DEVICE})
message(STATUS "Enabling magnetometer: ${FLIGHTCONTROLLER_MAGNETOMETER_DEVICE}")

register_module()
