////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       05.06.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef PADOPTIONS_H
#define PADOPTIONS_H

#include <QString>

class PadOptions {
public:
    void save(QString name);
    void loadDevice();
    void loadKeyMappings(QString name);

public:
    QString device;
    QString keyThrottle;
    QString keyRotate;
    QString keyFrontBack;
    QString keyLeftRight;
    QString keyLandingGear;
    QString keyMainLights;
    QString keyBottomLights;
    QString keyReturnBase;
    QString keyStabilizeFlight;
    QString keyFPV;
    QString keyFunc11;
    QString keyFunc12;
    QString keyFunc13;
    QString keyFunc14;
    QString keyFunc15;
    QString keyFunc16;
};

#endif
