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
    settings.setValue("keyFunc11", keyFunc11);
    settings.setValue("keyFunc12", keyFunc12);
    settings.setValue("keyFunc13", keyFunc13);
    settings.setValue("keyFunc14", keyFunc14);
    settings.setValue("keyFunc15", keyFunc15);
    settings.setValue("keyFunc16", keyFunc16);
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
    keyThrottle = settings.value("keyThrottle", "").toString();
    keyRotate = settings.value("keyRotate", "").toString();
    keyFrontBack = settings.value("keyFrontBack", "").toString();
    keyLeftRight = settings.value("keyLeftRight", "").toString();
    keyLandingGear = settings.value("keyLandingGear", "").toString();
    keyMainLights = settings.value("keyMainLights", "").toString();
    keyBottomLights = settings.value("keyBottomLights", "").toString();
    keyReturnBase = settings.value("keyReturnBase", "").toString();
    keyStabilizeFlight = settings.value("keyStabilizeFlight", "").toString();
    keyFPV = settings.value("keyFPV", "").toString();
    keyFunc11 = settings.value("keyFunc11", "").toString();
    keyFunc12 = settings.value("keyFunc12", "").toString();
    keyFunc13 = settings.value("keyFunc13", "").toString();
    keyFunc14 = settings.value("keyFunc14", "").toString();
    keyFunc15 = settings.value("keyFunc15", "").toString();
    keyFunc16 = settings.value("keyFunc16", "").toString();
    settings.endGroup();
}
