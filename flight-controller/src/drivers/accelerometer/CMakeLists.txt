set(SOURCES
    accelerometer.h
)

add_subdirectory(${FLIGHTCONTROLLER_ACCELEROMETER_DEVICE})
message(STATUS "Enabling accelerometer: ${FLIGHTCONTROLLER_ACCELEROMETER_DEVICE}")

register_module()
