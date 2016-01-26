////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       01.12.2014
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "LogsOptions.h"

#include <QDir>

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

void NetworkServerOptions::save(QSettings& settings)
{
    settings.beginGroup("NetworkServerOptions");
    settings.setValue("address", address);
    settings.setValue("port", port);
    settings.endGroup();
}

void NetworkServerOptions::load(QSettings& settings)
{
    settings.beginGroup("NetworkServerOptions");
    address = settings.value("address", "127.0.0.1").toString();
    port = settings.value("port", 12555).toUInt();
    settings.endGroup();
}

void LogsOptions::save()
{
    QSettings settings;

    settings.beginGroup("LogsOptions");
    settings.setValue("serialLogsEnabled", serialLogsEnabled);
    settings.setValue("logsPath", logsPath);
    settings.beginGroup("SerialLogs");
    serialLogs.save(settings);
    settings.endGroup();
    settings.beginGroup("NetworkLogs");
    networkLogs.save(settings);
    settings.endGroup();
    settings.endGroup();
}

void LogsOptions::load()
{
    QSettings settings;

    settings.beginGroup("LogsOptions");
    serialLogsEnabled = settings.value("serialLogsEnabled", true).toBool();
    logsPath = settings.value("logsPath", QDir::currentPath()).toString();
    settings.beginGroup("SerialLogs");
    serialLogs.load(settings);
    settings.endGroup();
    settings.beginGroup("NetworkLogs");
    networkLogs.load(settings);
    settings.endGroup();
    settings.endGroup();
}
