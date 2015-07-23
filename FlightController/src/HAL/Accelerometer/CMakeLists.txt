set(SOURCES
    Accelerometer.h
)

if(${FLIGHTCONTROLLER_USE_ACCELEROMETER})
    add_subdirectory(${FLIGHTCONTROLLER_ACCELEROMETER_DEVICE})
    message(STATUS "Enabling accelerometer: ${FLIGHTCONTROLLER_ACCELEROMETER_DEVICE}")
else()
    message(STATUS "Accelerometer disabled")
endif()

RegisterModule()
