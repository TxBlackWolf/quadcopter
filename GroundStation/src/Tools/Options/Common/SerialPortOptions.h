////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       05.02.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef SERIALPORTOPTIONS_H
#define SERIALPORTOPTIONS_H

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

#endif
