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
    int keyThrottle;
    int keyRotate;
    int keyFrontBack;
    int keyLeftRight;
    int keyLandingGear;
    int keyMainLights;
    int keyBottomLights;
    int keyReturnBase;
    int keyStabilizeFlight;
    int keyFPV;
};

#endif
