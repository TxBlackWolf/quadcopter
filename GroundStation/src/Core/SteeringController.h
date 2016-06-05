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

#include <QObject>

class SteeringController : public QObject {
    Q_OBJECT

public:
    typedef enum {
        STEERING_EVENT_THROTTLE,
        STEERING_EVENT_ROTATE,
        STEERING_EVENT_FRONT_BACK,
        STEERING_EVENT_LEFT_RIGHT,
        STEERING_EVENT_LANDING_GEAR,
        STEERING_EVENT_MAIN_LIGHTS,
        STEERING_EVENT_BOTTOM_LIGHTS,
        STEERING_EVENT_RETURN_BASE
    } SteeringEvents;

public slots:
    void handleEvent(SteeringEvents type, int value);

private:
    void sendThrottleCommand(int value);
};

#endif
