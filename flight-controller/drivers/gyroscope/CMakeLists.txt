set(SOURCES
    gyroscope.h
)

add_subdirectory(${FLIGHTCONTROLLER_GYROSCOPE_DEVICE})
message(STATUS "Enabling gyroscope: ${FLIGHTCONTROLLER_GYROSCOPE_DEVICE}")

register_module()
