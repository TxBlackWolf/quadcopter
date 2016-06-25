////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       05.06.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "PadOptions.h"
#include "Core/SteeringController.h"

#include <QSettings>

void PadOptions::save(QString name)
{
    QSettings settings;

    settings.setValue("device", device);
    settings.beginGroup(name);
    settings.setValue("keyThrottle", keyThrottle);
    settings.setValue("keyRotate", keyRotate);
    settings.setValue("keyFrontBack", keyFrontBack);
    settings.setValue("keyLeftRight", keyLeftRight);
    settings.setValue("keyLandingGear", keyLandingGear);
    settings.setValue("keyMainLights", keyMainLights);
    settings.setValue("keyBottomLights", keyBottomLights);
    settings.setValue("keyReturnBase", keyReturnBase);
    settings.setValue("keyStabilizeFlight", keyStabilizeFlight);
    settings.setValue("keyFPV", keyFPV);
    settings.endGroup();
}

void PadOptions::loadDevice()
{
    QSettings settings;
    device = settings.value("device", "").toString();
}

void PadOptions::loadKeyMappings(QString name)
{
    QSettings settings;

    settings.beginGroup(name);
    keyThrottle = settings.value("keyThrottle", UNDEFINED_KEY_ID).toInt();
    keyRotate = settings.value("keyRotate", UNDEFINED_KEY_ID).toInt();
    keyFrontBack = settings.value("keyFrontBack", UNDEFINED_KEY_ID).toInt();
    keyLeftRight = settings.value("keyLeftRight", UNDEFINED_KEY_ID).toInt();
    keyLandingGear = settings.value("keyLandingGear", UNDEFINED_KEY_ID).toInt();
    keyMainLights = settings.value("keyMainLights", UNDEFINED_KEY_ID).toInt();
    keyBottomLights = settings.value("keyBottomLights", UNDEFINED_KEY_ID).toInt();
    keyReturnBase = settings.value("keyReturnBase", UNDEFINED_KEY_ID).toInt();
    keyStabilizeFlight = settings.value("keyStabilizeFlight", UNDEFINED_KEY_ID).toInt();
    keyFPV = settings.value("keyFPV", UNDEFINED_KEY_ID).toInt();
    settings.endGroup();
}
