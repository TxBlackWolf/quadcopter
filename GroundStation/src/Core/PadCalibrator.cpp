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

static const char *XBOX_ONE_PAD_NAME = "Microsoft X-Box One pad";

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

const char *XBoxOnePadCalibrator::getAxisName(int id)
{
    static const char *axisNames[ABS_MAX + 1] = {
        "X", "Y", "Z", "Rx", "Ry", "Rz", "Left/Right Arrow", "Up/Down Arrow", "Wheel", "Gas", "Brake", "?", "?", "?", "?", "?",
        "Hat0X", "Hat0Y", "Hat1X", "Hat1Y", "Hat2X", "Hat2Y", "Hat3X", "Hat3Y", "?", "?", "?", "?", "?", "?", "?"
    };

    return axisNames[id];
}

const char *XBoxOnePadCalibrator::getButtonName(int id)
{
    static const char *buttonNames[KEY_MAX - BTN_MISC + 1] = {
        "A", "B", "X", "Y", "LB", "RB", "Start", "Select", "XBox One", "Btn9", "?", "?", "?", "?", "?", "?",
        "LeftBtn", "RightBtn", "MiddleBtn", "SideBtn", "ExtraBtn", "ForwardBtn", "BackBtn", "TaskBtn", "?", "?", "?",
        "?", "?", "?", "?", "?", "Trigger", "ThumbBtn", "ThumbBtn2", "TopBtn", "TopBtn2", "PinkieBtn", "BaseBtn", "BaseBtn2",
        "BaseBtn3", "BaseBtn4", "BaseBtn5", "BaseBtn6", "BtnDead", "BtnA", "BtnB", "BtnC", "BtnX", "BtnY", "BtnZ", "BtnTL",
        "BtnTR", "BtnTL2", "BtnTR2", "BtnSelect", "BtnStart", "BtnMode", "BtnThumbL", "BtnThumbR", "?", "?", "?", "?", "?",
        "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "WheelBtn", "Gear up"
    };

    return buttonNames[id];
}
