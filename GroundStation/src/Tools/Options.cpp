//---------------------------------------------------------------------------------------------------------------
//
// Filename   : Options.cpp
// Author     : Kuba Sejdak
// Created on : 01.12.2014
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#include "Options.h"

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

void LogsOptions::save()
{
    QSettings settings;

    settings.beginGroup("LogsOptions");
    settings.beginGroup("SerialLogs");
    serialLogs.save(settings);
    settings.endGroup();
    settings.beginGroup("RadioLogs");
    radioLogs.save(settings);
    settings.endGroup();
    settings.endGroup();
}

void LogsOptions::load()
{
    QSettings settings;

    settings.beginGroup("LogsOptions");
    settings.beginGroup("SerialLogs");
    serialLogs.load(settings);
    settings.endGroup();
    settings.beginGroup("RadioLogs");
    radioLogs.load(settings);
    settings.endGroup();
    settings.endGroup();
}
