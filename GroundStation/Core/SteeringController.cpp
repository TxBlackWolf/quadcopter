////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       05.06.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "SteeringController.h"
#include "command/command_control.h"
#include "command/command_encoder.h"

#include <cstdint>

SteeringController::SteeringController(CommandsManager& commandsManager)
    : m_commandsManager(commandsManager)
{
    for(int i = 0; i < AXIS_STEERING_COUNT; ++i)
        m_axisMapping[i] = UNDEFINED_KEY_ID;

    for(int i = 0; i < BUTTON_STEERING_COUNT; ++i)
        m_buttonMapping[i] = UNDEFINED_KEY_ID;
}

void SteeringController::registerAxisEvent(int id, AxisSteeringEvent type)
{
    m_axisMapping[type] = id;
}

void SteeringController::registerButtonEvent(int id, ButtonSteeringEvent type)
{
    m_buttonMapping[type] = id;
}

#include <QDebug>
void SteeringController::handleAxisEvent(int id, int value)
{
    // Note: We allow mapping more than one event for the same key.
    for(int i = 0 ; i < AXIS_STEERING_COUNT; ++i) {
        if (m_axisMapping[i] == id) {
            AxisSteeringEvent type = static_cast<AxisSteeringEvent>(i);
            switch (type) {
            case AXIS_STEERING_THROTTLE:
                sendThrottleCommand(value);
                break;

            case AXIS_STEERING_ROTATE:
                qDebug() << "Sending rotate: " << value << " %";
                break;

            case AXIS_STEERING_FRONT_BACK:
                qDebug() << "Sending front/back: " << value << " %";
                break;

            case AXIS_STEERING_LEFT_RIGHT:
                qDebug() << "Sending left/right: " << value << " %";
                break;

            default:
                break;
            }
        }
    }
}

void SteeringController::handleButtonEvent(int id, bool value)
{
    // We want only "press" events, not "release" ones.
    if (!value)
        return;

    // Note: We allow mapping more than one event for the same key.
    for(int i = 0 ; i < BUTTON_STEERING_COUNT; ++i) {
        if (m_buttonMapping[i] == id) {
            ButtonSteeringEvent type = static_cast<ButtonSteeringEvent>(i);
            switch (type) {
            case BUTTON_STEERING_LANDING_GEAR:
                qDebug() << "Sending landing gear";
                break;

            case BUTTON_STEERING_MAIN_LIGHTS:
                qDebug() << "Sending main lights";
                break;

            case BUTTON_STEERING_BOTTOM_LIGHTS:
                qDebug() << "Sending bottom lights";
                break;

            case BUTTON_STEERING_RETURN_BASE:
                qDebug() << "Sending return to base";
                break;

            case BUTTON_STEERING_STABILIZE_FLIGHT:
                qDebug() << "Sending stabilize flight";
                break;

            case BUTTON_STEERING_FPV:
                qDebug() << "Sending FPV";
                break;

            default:
                break;
            }
        }
    }
}

void SteeringController::sendThrottleCommand(int value)
{
    ControlCommandThrottle_t throttle_command;
    throttle_command.throttle = static_cast<int8_t>(value);

    uint8_t command[COMMAND_MAX_SIZE_BYTES];
    int command_size = commandEncoder_createControlCommand(command, CONTROL_EVENT_THROTTLE, &throttle_command);

    m_commandsManager.sendCommand(command, command_size);
}
