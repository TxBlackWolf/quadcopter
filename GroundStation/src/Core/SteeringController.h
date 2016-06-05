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
        STEERING_EVENT_YAW,
        STEERING_EVENT_PITCH,
        STEERING_EVENT_ROLL,
        STEERING_EVENT_LANDING_GEAR
    } SteeringEvents;

    SteeringController();
    virtual ~SteeringController();
};

#endif
