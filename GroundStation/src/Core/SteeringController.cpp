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

void SteeringController::handleEvent(SteeringEvents type, int value)
{
    switch(type) {
    case STEERING_EVENT_THROTTLE:
        sendThrottleCommand(value);
        break;

    case STEERING_EVENT_ROTATE:
        break;

    case STEERING_EVENT_FRONT_BACK:
        break;

    case STEERING_EVENT_LEFT_RIGHT:
        break;

    case STEERING_EVENT_LANDING_GEAR:
        break;

    case STEERING_EVENT_MAIN_LIGHTS:
        break;

    case STEERING_EVENT_BOTTOM_LIGHTS:
        break;

    case STEERING_EVENT_RETURN_BASE:
        break;

    default:
        break;
    }
}

void SteeringController::sendThrottleCommand(int value)
{
}
