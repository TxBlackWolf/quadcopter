////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       05.02.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "SerialPortOptions.h"

void SerialPortOptions::save(QSettings& settings)
{
    settings.beginGroup("SerialPortOptions");
    settings.setValue("portName", portName);
    settings.setValue("baudRate", baudRate);
    settings.setValue("dataBits", dataBits);
    settings.setValue("partity", partity);
    settings.setValue("stopBits", stopBits);
    settings.setValue("flowControl", flowControl);
    settings.endGroup();
}

void SerialPortOptions::load(QSettings& settings)
{
    settings.beginGroup("SerialPortOptions");
    portName = settings.value("portName", "").toString();
    baudRate = settings.value("baudRate", 115200).toInt();
    dataBits = (QSerialPort::DataBits) settings.value("dataBits", QSerialPort::Data8).toInt();
    partity = (QSerialPort::Parity) settings.value("partity", QSerialPort::NoParity).toInt();
    stopBits = (QSerialPort::StopBits) settings.value("stopBits", QSerialPort::OneStop).toInt();
    flowControl = (QSerialPort::FlowControl) settings.value("flowControl", QSerialPort::NoFlowControl).toInt();
    settings.endGroup();
}
