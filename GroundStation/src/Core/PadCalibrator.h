////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       27.05.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef PADCALIBRATOR_H
#define PADCALIBRATOR_H

#include <memory>
#include <string>

class IPadCalibrator {
public:
    static std::unique_ptr<IPadCalibrator> create(std::string name);
    virtual ~IPadCalibrator() {}

    virtual const char *getAxisName(int id) = 0;
    virtual const char *getButtonName(int id) = 0;
};

class GenericPadCalibrator : public IPadCalibrator {
public:
    virtual const char *getAxisName(int id);
    virtual const char *getButtonName(int id);
};

class XBoxOnePadCalibrator : public IPadCalibrator {
public:
    virtual const char *getAxisName(int id);
    virtual const char *getButtonName(int id);
};

#endif
