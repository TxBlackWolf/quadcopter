set(SOURCES
    buzzer.h
)

add_subdirectory(${FLIGHTCONTROLLER_BUZZER_DEVICE})
message(STATUS "Enabling buzzer: ${FLIGHTCONTROLLER_BUZZER_DEVICE}")

register_module()
