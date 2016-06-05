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

#include <linux/joystick.h>
#include <memory>
#include <string>

static const int AXES_MAX_COUNT    = ABS_MAX + 1;
static const int BUTTONS_MAX_COUNT = KEY_MAX - BTN_MISC + 1;

class IPadCalibrator {
public:
    static std::unique_ptr<IPadCalibrator> create(std::string name);
    virtual ~IPadCalibrator() = default;

    static const char *getAxisName(int id);
    static const char *getButtonName(int id);

    virtual int normalizeAxisAngle(int originalAngle) = 0;
    virtual bool normalizeButtonState(int originalState) = 0;
    virtual void setSensitivity(int sensitivity) = 0;

public:
    static const char **axesNames;
    static const char **buttonsNames;
};

class GenericPadCalibrator : public IPadCalibrator {
public:
    GenericPadCalibrator();

    virtual int normalizeAxisAngle(int originalAngle);
    virtual bool normalizeButtonState(int originalState);
    virtual void setSensitivity(int) {}

public:
    static const char *genericAxes[AXES_MAX_COUNT];
    static const char *genericButtons[BUTTONS_MAX_COUNT];
};

class XBoxOnePadCalibrator : public IPadCalibrator {
public:
    XBoxOnePadCalibrator();

    virtual int normalizeAxisAngle(int originalAngle);
    virtual bool normalizeButtonState(int originalState);
    virtual void setSensitivity(int sensitivity);

public:
    static constexpr const char *name = "Microsoft X-Box One pad";
    static const char *xboxAxes[AXES_MAX_COUNT];
    static const char *xboxButtons[BUTTONS_MAX_COUNT];

private:
    const int m_boundary;
    int m_sensitivity;
    int m_step;
};

#endif
