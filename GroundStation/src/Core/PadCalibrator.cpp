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

#include <cstring>
#include <linux/joystick.h>

static const char *XBOX_ONE_PAD_NAME          = "Microsoft X-Box One pad";
static const int XBOX_ONE_AXIS_BOUNDARY_VALUE = 32767;
static const int XBOX_ONE_AXIS_CALIB_STEP     = 50;
static const float XBOX_ONE_AXIS_CALIB_COEFF  = XBOX_ONE_AXIS_BOUNDARY_VALUE / XBOX_ONE_AXIS_CALIB_STEP;

std::unique_ptr<IPadCalibrator> IPadCalibrator::create(std::string name)
{
    if(strcmp(name.c_str(), XBOX_ONE_PAD_NAME) == 0)
        return std::unique_ptr<IPadCalibrator>(new XBoxOnePadCalibrator());

    return std::unique_ptr<IPadCalibrator>(new GenericPadCalibrator());
}

const char *GenericPadCalibrator::getAxisName(int id)
{
    static const char *axisNames[ABS_MAX + 1] = {
        "X", "Y", "Z", "Rx", "Ry", "Rz", "Throttle", "Rudder", "Wheel", "Gas", "Brake", "?", "?", "?", "?", "?",
        "Hat0X", "Hat0Y", "Hat1X", "Hat1Y", "Hat2X", "Hat2Y", "Hat3X", "Hat3Y", "?", "?", "?", "?", "?", "?", "?"
    };

    return axisNames[id];
}

const char *GenericPadCalibrator::getButtonName(int id)
{
    static const char *buttonNames[KEY_MAX - BTN_MISC + 1] = {
        "Btn0", "Btn1", "Btn2", "Btn3", "Btn4", "Btn5", "Btn6", "Btn7", "Btn8", "Btn9", "?", "?", "?", "?", "?", "?",
        "LeftBtn", "RightBtn", "MiddleBtn", "SideBtn", "ExtraBtn", "ForwardBtn", "BackBtn", "TaskBtn", "?", "?", "?",
        "?", "?", "?", "?", "?", "Trigger", "ThumbBtn", "ThumbBtn2", "TopBtn", "TopBtn2", "PinkieBtn", "BaseBtn", "BaseBtn2",
        "BaseBtn3", "BaseBtn4", "BaseBtn5", "BaseBtn6", "BtnDead", "BtnA", "BtnB", "BtnC", "BtnX", "BtnY", "BtnZ", "BtnTL",
        "BtnTR", "BtnTL2", "BtnTR2", "BtnSelect", "BtnStart", "BtnMode", "BtnThumbL", "BtnThumbR", "?", "?", "?", "?", "?",
        "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "WheelBtn", "Gear up"
    };

    return buttonNames[id];
}

int GenericPadCalibrator::normalizeAxisAngle(int originalAngle)
{
    return originalAngle;
}

bool GenericPadCalibrator::normalizeButtonState(int originalState)
{
    return (originalState != 0);
}

const char *XBoxOnePadCalibrator::getAxisName(int id)
{
    static const char *axisNames[ABS_MAX + 1] = {
        "JoyLX", "JoyLY", "LT", "JoyRX", "JoyRY", "RT", "Left/Right Arrow", "Up/Down Arrow", "Wheel", "Gas", "Brake", "Ax1",
        "Ax2", "Ax3", "Ax4", "Ax5", "Hat0X", "Hat0Y", "Hat1X", "Hat1Y", "Hat2X", "Hat2Y", "Hat3X", "Hat3Y", "Ax6", "Ax7",
        "Ax8", "Ax9", "Ax10", "Ax11", "Ax12"
    };

    return axisNames[id];
}

const char *XBoxOnePadCalibrator::getButtonName(int id)
{
    static const char *buttonNames[KEY_MAX - BTN_MISC + 1] = {
        "A", "B", "X", "Y", "LB", "RB", "Start", "Select", "XBox One", "JoyL", "JoyR", "B2", "B3", "B4", "B5", "B6",
        "LeftBtn", "RightBtn", "MiddleBtn", "SideBtn", "ExtraBtn", "ForwardBtn", "BackBtn", "TaskBtn", "B7", "B8", "B9",
        "B10", "B11", "B12", "B13", "B14", "Trigger", "ThumbBtn", "ThumbBtn2", "TopBtn", "TopBtn2", "PinkieBtn", "BaseBtn",
        "BaseBtn2", "BaseBtn3", "BaseBtn4", "BaseBtn5", "BaseBtn6", "BtnDead", "BtnA", "BtnB", "BtnC", "BtnX", "BtnY", "BtnZ",
        "BtnTL", "BtnTR", "BtnTL2", "BtnTR2", "BtnSelect", "BtnStart", "BtnMode", "BtnThumbL", "BtnThumbR", "B15", "B16", "B17",
        "B18", "B19", "B20", "B21", "B22", "B23", "B24", "B25", "B26", "B27", "B28", "B29", "B30", "B31", "WheelBtn", "Gear up"
    };

    return buttonNames[id];
}

int XBoxOnePadCalibrator::normalizeAxisAngle(int originalAngle)
{
    // Revert polarization of axis value.
    return -((originalAngle / XBOX_ONE_AXIS_CALIB_COEFF) * (100.0f / XBOX_ONE_AXIS_CALIB_STEP));
}

bool XBoxOnePadCalibrator::normalizeButtonState(int originalState)
{
    return (originalState == 1);
}
