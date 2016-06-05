////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       06.05.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef STEERINGCONTROLLER_H
#define STEERINGCONTROLLER_H

#include "Core/PadDriver.h"

#include <QObject>

class SteeringController : public QObject {
    Q_OBJECT

public:
    typedef enum {
        AXIS_STEERING_THROTTLE,
        AXIS_STEERING_ROTATE,
        AXIS_STEERING_FRONT_BACK,
        AXIS_STEERING_LEFT_RIGHT,
        AXIS_STEERING_COUNT
    } AxisSteeringEvent;

    typedef enum {
        BUTTON_STEERING_LANDING_GEAR,
        BUTTON_STEERING_MAIN_LIGHTS,
        BUTTON_STEERING_BOTTOM_LIGHTS,
        BUTTON_STEERING_RETURN_BASE,
        BUTTON_STEERING_STABILIZE_FLIGHT,
        BUTTON_STEERING_FPV,
        BUTTON_STEERING_COUNT
    } ButtonSteeringEvent;

    SteeringController();

public slots:
    void registerAxisEvent(int id, SteeringController::AxisSteeringEvent type);
    void registerButtonEvent(int id, SteeringController::ButtonSteeringEvent type);
    void handleAxisEvent(int id, int value);
    void handleButtonEvent(int id, bool value);

private:
    void sendThrottleCommand(int value);

private:
    AxisSteeringEvent m_axisMapping[AXIS_MAP_SIZE];
    ButtonSteeringEvent m_buttonMapping[BUTTON_MAP_SIZE];
};

#endif
