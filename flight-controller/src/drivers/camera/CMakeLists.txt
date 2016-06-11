set(SOURCES
    camera.h
)

add_subdirectory(${FLIGHTCONTROLLER_CAMERA_DEVICE})
message(STATUS "Enabling camera: ${FLIGHTCONTROLLER_CAMERA_DEVICE}")

register_module()
