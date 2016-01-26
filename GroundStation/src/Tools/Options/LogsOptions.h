////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       01.12.2014
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef LOGSOPTIONS_H
#define LOGSOPTIONS_H

#include <QSerialPort>
#include <QSettings>
#include <QString>

class SerialPortOptions {
public:
    void save(QSettings& settings);
    void load(QSettings& settings);

public:
    QString portName;
    unsigned int baudRate;
    QSerialPort::DataBits dataBits;
    QSerialPort::Parity partity;
    QSerialPort::StopBits stopBits;
    QSerialPort::FlowControl flowControl;
};

class NetworkServerOptions {
public:
    void save(QSettings& settings);
    void load(QSettings& settings);

public:
    QString address;
    unsigned int port;
};

class LogsOptions {
public:
    void save();
    void load();

public:
    bool serialLogsEnabled;
    SerialPortOptions serialLogs;
    NetworkServerOptions networkLogs;
};

#endif
