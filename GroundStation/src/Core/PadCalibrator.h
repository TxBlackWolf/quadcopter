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
    virtual int normalizeAxisAngle(int originalAngle) = 0;
    virtual bool normalizeButtonState(int originalState) = 0;
};

class GenericPadCalibrator : public IPadCalibrator {
public:
    virtual const char *getAxisName(int id);
    virtual const char *getButtonName(int id);
    virtual int normalizeAxisAngle(int originalAngle);
    virtual bool normalizeButtonState(int originalState);
};

class XBoxOnePadCalibrator : public IPadCalibrator {
public:
    virtual const char *getAxisName(int id);
    virtual const char *getButtonName(int id);
    virtual int normalizeAxisAngle(int originalAngle);
    virtual bool normalizeButtonState(int originalState);
};

#endif
