////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       27.05.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "PadCalibrator.h"
#include "Core/SteeringController.h"

#include <cstring>

const char **IPadCalibrator::axesNames = nullptr;
const char **IPadCalibrator::buttonsNames = nullptr;

std::unique_ptr<IPadCalibrator> IPadCalibrator::create(std::string name)
{
    if(strcmp(name.c_str(), XBoxOnePadCalibrator::name) == 0)
        return std::unique_ptr<IPadCalibrator>(new XBoxOnePadCalibrator());

    return std::unique_ptr<IPadCalibrator>(new GenericPadCalibrator());
}

const char *IPadCalibrator::getAxisName(int id)
{
    if(!axesNames)
        return "";

    return axesNames[id];
}

int IPadCalibrator::getAxisId(const char *name)
{
    for(int i = 0; i < AXES_MAX_COUNT; ++i) {
        if(strcmp(name, axesNames[i]) == 0)
            return i;
    }

    return UNDEFINED_KEY_ID;
}

const char *IPadCalibrator::getButtonName(int id)
{
    if(!buttonsNames)
        return "";

    return buttonsNames[id];
}

int IPadCalibrator::getButtonId(const char *name)
{
    for(int i = 0; i < BUTTONS_MAX_COUNT; ++i) {
        if(strcmp(name, buttonsNames[i]) == 0)
            return i;
    }

    return UNDEFINED_KEY_ID;
}

const char *GenericPadCalibrator::genericAxes[AXES_MAX_COUNT] = {
    "X", "Y", "Z", "Rx", "Ry", "Rz", "Throttle", "Rudder", "Wheel", "Gas", "Brake", "?", "?", "?", "?", "?",
    "Hat0X", "Hat0Y", "Hat1X", "Hat1Y", "Hat2X", "Hat2Y", "Hat3X", "Hat3Y", "?", "?", "?", "?", "?", "?", "?"
};

const char *GenericPadCalibrator::genericButtons[BUTTONS_MAX_COUNT] = {
    "Btn0", "Btn1", "Btn2", "Btn3", "Btn4", "Btn5", "Btn6", "Btn7", "Btn8", "Btn9", "?", "?", "?", "?", "?", "?",
    "LeftBtn", "RightBtn", "MiddleBtn", "SideBtn", "ExtraBtn", "ForwardBtn", "BackBtn", "TaskBtn", "?", "?", "?",
    "?", "?", "?", "?", "?", "Trigger", "ThumbBtn", "ThumbBtn2", "TopBtn", "TopBtn2", "PinkieBtn", "BaseBtn", "BaseBtn2",
    "BaseBtn3", "BaseBtn4", "BaseBtn5", "BaseBtn6", "BtnDead", "BtnA", "BtnB", "BtnC", "BtnX", "BtnY", "BtnZ", "BtnTL",
    "BtnTR", "BtnTL2", "BtnTR2", "BtnSelect", "BtnStart", "BtnMode", "BtnThumbL", "BtnThumbR", "?", "?", "?", "?", "?",
    "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "WheelBtn", "Gear up"
};

GenericPadCalibrator::GenericPadCalibrator()
{
    axesNames = genericAxes;
    buttonsNames = genericButtons;
}

int GenericPadCalibrator::normalizeAxisAngle(int originalAngle)
{
    return originalAngle;
}

bool GenericPadCalibrator::normalizeButtonState(int originalState)
{
    return (originalState != 0);
}

const char *XBoxOnePadCalibrator::xboxAxes[AXES_MAX_COUNT] = {
    "JoyLX", "JoyLY", "LT", "JoyRX", "JoyRY", "RT", "LR Arrow", "UD Arrow", "Wheel", "Gas", "Brake", "Ax1",
    "Ax2", "Ax3", "Ax4", "Ax5", "Hat0X", "Hat0Y", "Hat1X", "Hat1Y", "Hat2X", "Hat2Y", "Hat3X", "Hat3Y", "Ax6", "Ax7",
    "Ax8", "Ax9", "Ax10", "Ax11", "Ax12"
};

const char *XBoxOnePadCalibrator::xboxButtons[BUTTONS_MAX_COUNT] = {
    "A", "B", "X", "Y", "LB", "RB", "Start", "Select", "XBox One", "JoyL", "JoyR", "B2", "B3", "B4", "B5", "B6",
    "LeftBtn", "RightBtn", "MiddleBtn", "SideBtn", "ExtraBtn", "ForwardBtn", "BackBtn", "TaskBtn", "B7", "B8", "B9",
    "B10", "B11", "B12", "B13", "B14", "Trigger", "ThumbBtn", "ThumbBtn2", "TopBtn", "TopBtn2", "PinkieBtn", "BaseBtn",
    "BaseBtn2", "BaseBtn3", "BaseBtn4", "BaseBtn5", "BaseBtn6", "BtnDead", "BtnA", "BtnB", "BtnC", "BtnX", "BtnY", "BtnZ",
    "BtnTL", "BtnTR", "BtnTL2", "BtnTR2", "BtnSelect", "BtnStart", "BtnMode", "BtnThumbL", "BtnThumbR", "B15", "B16", "B17",
    "B18", "B19", "B20", "B21", "B22", "B23", "B24", "B25", "B26", "B27", "B28", "B29", "B30", "B31", "WheelBtn", "Gear up"
};

XBoxOnePadCalibrator::XBoxOnePadCalibrator()
    : m_boundary(32767)
    , m_sensitivity(100)
    , m_step(m_boundary / m_sensitivity)
{
    axesNames = xboxAxes;
    buttonsNames = xboxButtons;
}

int XBoxOnePadCalibrator::normalizeAxisAngle(int originalAngle)
{
    // Revert polarization of axis value.
    return -((originalAngle / m_step) * (100.0f / m_sensitivity));
}

bool XBoxOnePadCalibrator::normalizeButtonState(int originalState)
{
    return (originalState == 1);
}

void XBoxOnePadCalibrator::setSensitivity(int sensitivity)
{
    m_sensitivity = sensitivity;
    m_step = m_boundary / m_sensitivity;
}
