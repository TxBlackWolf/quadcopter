set(SOURCES
    buzzer.h
)

if(${FLIGHTCONTROLLER_USE_BUZZER})
    add_subdirectory(${FLIGHTCONTROLLER_BUZZER_DEVICE})
    message(STATUS "Enabling buzzer: ${FLIGHTCONTROLLER_BUZZER_DEVICE}")
else()
    message(STATUS "Buzzer disabled")
endif()

register_module()
