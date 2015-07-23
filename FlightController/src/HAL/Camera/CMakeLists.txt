set(SOURCES
    Camera.h
)

if(${FLIGHTCONTROLLER_USE_CAMERA})
    add_subdirectory(${FLIGHTCONTROLLER_CAMERA_DEVICE})
    message(STATUS "Enabling camera: ${FLIGHTCONTROLLER_CAMERA_DEVICE}")
else()
    message(STATUS "Camera disabled")
endif()

RegisterModule()
