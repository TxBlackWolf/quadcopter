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

SteeringController::SteeringController()
{
    for(int i = 0; i < AXIS_MAP_SIZE; ++i)
        m_axisMapping[i] = AXIS_STEERING_COUNT;

    for(int i = 0; i < BUTTON_MAP_SIZE; ++i)
        m_buttonMapping[i] = BUTTON_STEERING_COUNT;
}

void SteeringController::registerAxisEvent(int id, AxisSteeringEvent type)
{
    m_axisMapping[id] = type;
}

void SteeringController::registerButtonEvent(int id, ButtonSteeringEvent type)
{
    m_buttonMapping[id] = type;
}

#include <QDebug>
void SteeringController::handleAxisEvent(int id, int value)
{
    switch(m_axisMapping[id]) {
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

void SteeringController::handleButtonEvent(int id, bool value)
{
    // We want only "press" events, not "release" ones.
    if(!value)
        return;

    switch(m_buttonMapping[id]) {
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

void SteeringController::sendThrottleCommand(int value)
{
    qDebug() << "Sending throttle: " << value << " %";
}
