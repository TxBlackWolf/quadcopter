//============================================================================
//
// Filename   : Options.h
// Author     : Kuba Sejdak
// Created on : 1 gru 2014
//
//============================================================================

#ifndef OPTIONS_H
#define OPTIONS_H

#include <QSettings>
#include <QString>
#include <QSerialPort>

class SerialPortOptions
{
public:
    /// @brief Saves current serial port options.
    /// @param [in] settings        handle to settings object
    void save(QSettings& settings);

    /// @brief Loads current serial port options.
    /// /// @param [in] settings        handle to settings object
    void load(QSettings& settings);

public:
    QString portName;
    unsigned int baudRate;
    QSerialPort::DataBits dataBits;
    QSerialPort::Parity partity;
    QSerialPort::StopBits stopBits;
    QSerialPort::FlowControl flowControl;
};

class LogsOptions
{
public:
    /// @brief Saves current communication options.
    void save();

    /// @brief Loads current communication options.
    void load();

public:
    SerialPortOptions serialLogs;
    SerialPortOptions radioLogs;
};

#endif
