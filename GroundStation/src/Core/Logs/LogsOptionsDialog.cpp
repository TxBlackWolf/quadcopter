////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       28.11.2014
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "LogsOptionsDialog.h"
#include "ui_LogsOptionsDialog.h"

#include "Tools/Options.h"

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

LogsOptionsDialog::LogsOptionsDialog(QWidget* parent)
    : QDialog(parent)
    , m_ui(new Ui::LogsOptionsDialog)
{
    m_ui->setupUi(this);

    init();
}

LogsOptionsDialog::~LogsOptionsDialog()
{
    delete m_ui;
}

void LogsOptionsDialog::init()
{
    connect(m_ui->buttonBox, SIGNAL(accepted()), this, SLOT(saveOptions()));
    connect(m_ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(m_ui->comboBoxPortSerial, SIGNAL(currentIndexChanged(int)), this, SLOT(changeSerialLogsPortInfo(int)));
    connect(m_ui->comboBoxPortRadio, SIGNAL(currentIndexChanged(int)), this, SLOT(changeRadioLogsPortInfo(int)));

    initSerialPortOptions();
}

void LogsOptionsDialog::changeSerialLogsPortInfo(int currentPortIndex)
{
    QString portDescription = m_ui->comboBoxPortSerial->itemData(currentPortIndex).toString();
    m_ui->labelPortDescSerial->setText(portDescription);
}

void LogsOptionsDialog::changeRadioLogsPortInfo(int currentPortIndex)
{
    QString portDescription = m_ui->comboBoxPortRadio->itemData(currentPortIndex).toString();
    m_ui->labelPortDescRadio->setText(portDescription);
}

void LogsOptionsDialog::saveOptions()
{
    LogsOptions options;
    options.load();

    options.serialLogs.portName = m_ui->comboBoxPortSerial->currentText();
    options.serialLogs.baudRate = m_ui->comboBoxSpeedSerial->currentData().toInt();
    options.serialLogs.dataBits = (QSerialPort::DataBits) m_ui->comboBoxDataBitsSerial->currentData().toInt();
    options.serialLogs.stopBits = (QSerialPort::StopBits) m_ui->comboBoxStopBitsSerial->currentData().toInt();
    options.serialLogs.partity = (QSerialPort::Parity) m_ui->comboBoxPartitySerial->currentData().toInt();
    options.serialLogs.flowControl = (QSerialPort::FlowControl) m_ui->comboBoxFlowSerial->currentData().toInt();

    options.radioLogs.portName = m_ui->comboBoxPortRadio->currentText();
    options.radioLogs.baudRate = m_ui->comboBoxSpeedRadio->currentData().toInt();
    options.radioLogs.dataBits = (QSerialPort::DataBits) m_ui->comboBoxDataBitsRadio->currentData().toInt();
    options.radioLogs.stopBits = (QSerialPort::StopBits) m_ui->comboBoxStopBitsRadio->currentData().toInt();
    options.radioLogs.partity = (QSerialPort::Parity) m_ui->comboBoxPartityRadio->currentData().toInt();
    options.radioLogs.flowControl = (QSerialPort::FlowControl) m_ui->comboBoxFlowRadio->currentData().toInt();

    options.save();
    accept();
}

void LogsOptionsDialog::initSerialPortOptions()
{
    LogsOptions options;
    options.load();

    // Scan available serial ports.
    for(const QSerialPortInfo &info : QSerialPortInfo::availablePorts()) {
        m_ui->comboBoxPortSerial->addItem(info.portName(), info.description());
        m_ui->comboBoxPortRadio->addItem(info.portName(), info.description());
    }

    QString defaultSerialLogsPort = options.serialLogs.portName;
    int findResult = m_ui->comboBoxPortSerial->findText(defaultSerialLogsPort);
    if(findResult != -1)
        m_ui->comboBoxPortSerial->setCurrentIndex(findResult);

    QString defaultRadioPort = options.radioLogs.portName;
    findResult = m_ui->comboBoxPortRadio->findText(defaultRadioPort);
    if(findResult != -1)
        m_ui->comboBoxPortRadio->setCurrentIndex(findResult);

    // Scan available baud rates.
    auto standardSpeeds = QSerialPortInfo::standardBaudRates();
    for(unsigned int speed : standardSpeeds) {
        m_ui->comboBoxSpeedSerial->addItem(QString::number(speed), speed);
        m_ui->comboBoxSpeedRadio->addItem(QString::number(speed), speed);
    }

    unsigned int defaultSerialLogsSpeed = options.serialLogs.baudRate;
    findResult = m_ui->comboBoxSpeedSerial->findData(defaultSerialLogsSpeed);
    if(findResult != -1)
        m_ui->comboBoxSpeedSerial->setCurrentIndex(findResult);

    unsigned int defaultRadioLogsSpeed = options.radioLogs.baudRate;
    findResult = m_ui->comboBoxSpeedRadio->findData(defaultRadioLogsSpeed);
    if(findResult != -1)
        m_ui->comboBoxSpeedRadio->setCurrentIndex(findResult);

    // Set possible data bits.
    m_ui->comboBoxDataBitsSerial->addItem(QString::number(QSerialPort::Data5), QSerialPort::Data5);
    m_ui->comboBoxDataBitsSerial->addItem(QString::number(QSerialPort::Data6), QSerialPort::Data6);
    m_ui->comboBoxDataBitsSerial->addItem(QString::number(QSerialPort::Data7), QSerialPort::Data7);
    m_ui->comboBoxDataBitsSerial->addItem(QString::number(QSerialPort::Data8), QSerialPort::Data8);
    m_ui->comboBoxDataBitsRadio->addItem(QString::number(QSerialPort::Data5), QSerialPort::Data5);
    m_ui->comboBoxDataBitsRadio->addItem(QString::number(QSerialPort::Data6), QSerialPort::Data6);
    m_ui->comboBoxDataBitsRadio->addItem(QString::number(QSerialPort::Data7), QSerialPort::Data7);
    m_ui->comboBoxDataBitsRadio->addItem(QString::number(QSerialPort::Data8), QSerialPort::Data8);

    unsigned int defaultSerialLogsDataBits = options.serialLogs.dataBits;
    findResult = m_ui->comboBoxDataBitsSerial->findData(defaultSerialLogsDataBits);
    if(findResult != -1)
        m_ui->comboBoxDataBitsSerial->setCurrentIndex(findResult);

    unsigned int defaultRadioLogsDataBits = options.radioLogs.dataBits;
    findResult = m_ui->comboBoxDataBitsRadio->findData(defaultRadioLogsDataBits);
    if(findResult != -1)
        m_ui->comboBoxDataBitsRadio->setCurrentIndex(findResult);


    // Set possible stop bits.
    m_ui->comboBoxStopBitsSerial->addItem(QString::number(QSerialPort::OneStop), QSerialPort::OneStop);
    m_ui->comboBoxStopBitsSerial->addItem(QString::number(1.5), QSerialPort::OneAndHalfStop);
    m_ui->comboBoxStopBitsSerial->addItem(QString::number(QSerialPort::TwoStop), QSerialPort::TwoStop);
    m_ui->comboBoxStopBitsRadio->addItem(QString::number(QSerialPort::OneStop), QSerialPort::OneStop);
    m_ui->comboBoxStopBitsRadio->addItem(QString::number(1.5), QSerialPort::OneAndHalfStop);
    m_ui->comboBoxStopBitsRadio->addItem(QString::number(QSerialPort::TwoStop), QSerialPort::TwoStop);

    unsigned int defaultSerialLogsStopBits = options.serialLogs.stopBits;
    findResult = m_ui->comboBoxStopBitsSerial->findData(defaultSerialLogsStopBits);
    if(findResult != -1)
        m_ui->comboBoxStopBitsSerial->setCurrentIndex(findResult);

    unsigned int defaultRadioLogsStopBits = options.radioLogs.stopBits;
    findResult = m_ui->comboBoxStopBitsRadio->findData(defaultRadioLogsStopBits);
    if(findResult != -1)
        m_ui->comboBoxStopBitsRadio->setCurrentIndex(findResult);

    // Set possible bit partity.
    m_ui->comboBoxPartitySerial->addItem("None", QSerialPort::NoParity);
    m_ui->comboBoxPartitySerial->addItem("Even", QSerialPort::EvenParity);
    m_ui->comboBoxPartitySerial->addItem("Odd", QSerialPort::OddParity);
    m_ui->comboBoxPartitySerial->addItem("Space", QSerialPort::SpaceParity);
    m_ui->comboBoxPartitySerial->addItem("Mark", QSerialPort::MarkParity);
    m_ui->comboBoxPartityRadio->addItem("None", QSerialPort::NoParity);
    m_ui->comboBoxPartityRadio->addItem("Even", QSerialPort::EvenParity);
    m_ui->comboBoxPartityRadio->addItem("Odd", QSerialPort::OddParity);
    m_ui->comboBoxPartityRadio->addItem("Space", QSerialPort::SpaceParity);
    m_ui->comboBoxPartityRadio->addItem("Mark", QSerialPort::MarkParity);

    unsigned int defaultSerialLogsPartity = options.serialLogs.partity;
    findResult = m_ui->comboBoxPartitySerial->findData(defaultSerialLogsPartity);
    if(findResult != -1)
        m_ui->comboBoxPartitySerial->setCurrentIndex(findResult);

    unsigned int defaultRadioLogsPartity = options.radioLogs.partity;
    findResult = m_ui->comboBoxPartityRadio->findData(defaultRadioLogsPartity);
    if(findResult != -1)
        m_ui->comboBoxPartityRadio->setCurrentIndex(findResult);

    // Set possible flow control.
    m_ui->comboBoxFlowSerial->addItem("None", QSerialPort::NoFlowControl);
    m_ui->comboBoxFlowSerial->addItem("RTS/CTS", QSerialPort::HardwareControl);
    m_ui->comboBoxFlowSerial->addItem("XON/XOFF", QSerialPort::SoftwareControl);
    m_ui->comboBoxFlowRadio->addItem("None", QSerialPort::NoFlowControl);
    m_ui->comboBoxFlowRadio->addItem("RTS/CTS", QSerialPort::HardwareControl);
    m_ui->comboBoxFlowRadio->addItem("XON/XOFF", QSerialPort::SoftwareControl);

    unsigned int defaultSerialLogsFlow = options.serialLogs.flowControl;
    findResult = m_ui->comboBoxFlowSerial->findData(defaultSerialLogsFlow);
    if(findResult != -1)
        m_ui->comboBoxFlowSerial->setCurrentIndex(findResult);

    unsigned int defaultRadioLogsFlow = options.radioLogs.flowControl;
    findResult = m_ui->comboBoxFlowRadio->findData(defaultRadioLogsFlow);
    if(findResult != -1)
        m_ui->comboBoxFlowRadio->setCurrentIndex(findResult);

}
