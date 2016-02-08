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

#include <QFileDialog>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

LogsOptionsDialog::LogsOptionsDialog(QWidget* parent)
    : QDialog(parent)
    , m_ui(new Ui::LogsOptionsDialog())
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
    connect(m_ui->radioButtonSerial, SIGNAL(toggled(bool)), this, SLOT(radioButtonSerialToggled(bool)));
    connect(m_ui->radioButtonNetwork, SIGNAL(toggled(bool)), this, SLOT(radioButtonNetworkToggled(bool)));
    connect(m_ui->pushButtonLogsDir, SIGNAL(clicked()), this, SLOT(buttonSelectLogsDirClicked()));

    m_options.load();

    initSerialPortOptions();
    initNetworkOptions();

    radioButtonSerialToggled(m_options.serialLogsEnabled);
    radioButtonNetworkToggled(!m_options.serialLogsEnabled);

    m_ui->lineEditLogsDir->setText(m_options.logsPath);
}

void LogsOptionsDialog::changeSerialLogsPortInfo(int currentPortIndex)
{
    QString portDescription = m_ui->comboBoxPortSerial->itemData(currentPortIndex).toString();
    m_ui->labelPortDescSerial->setText(portDescription);
}

void LogsOptionsDialog::radioButtonSerialToggled(bool state)
{
    m_ui->radioButtonSerial->setChecked(state);
    m_ui->comboBoxPortSerial->setEnabled(state);
    m_ui->comboBoxSpeedSerial->setEnabled(state);
    m_ui->comboBoxDataBitsSerial->setEnabled(state);
    m_ui->comboBoxStopBitsSerial->setEnabled(state);
    m_ui->comboBoxPartitySerial->setEnabled(state);
    m_ui->comboBoxFlowSerial->setEnabled(state);
}

void LogsOptionsDialog::radioButtonNetworkToggled(bool state)
{
    m_ui->radioButtonNetwork->setChecked(state);
    m_ui->lineEditAddress->setEnabled(state);
    m_ui->lineEditPort->setEnabled(state);
}

void LogsOptionsDialog::buttonSelectLogsDirClicked()
{
    QString logsPath = QFileDialog::getExistingDirectory(this, "Save logs to");
    m_ui->lineEditLogsDir->setText(logsPath);
}

void LogsOptionsDialog::saveOptions()
{
    m_options.load();

    m_options.serialLogsEnabled = m_ui->radioButtonSerial->isChecked();
    m_options.logsPath = m_ui->lineEditLogsDir->text();

    m_options.serialLogs.portName = m_ui->comboBoxPortSerial->currentText();
    m_options.serialLogs.baudRate = m_ui->comboBoxSpeedSerial->currentData().toInt();
    m_options.serialLogs.dataBits = (QSerialPort::DataBits) m_ui->comboBoxDataBitsSerial->currentData().toInt();
    m_options.serialLogs.stopBits = (QSerialPort::StopBits) m_ui->comboBoxStopBitsSerial->currentData().toInt();
    m_options.serialLogs.partity = (QSerialPort::Parity) m_ui->comboBoxPartitySerial->currentData().toInt();
    m_options.serialLogs.flowControl = (QSerialPort::FlowControl) m_ui->comboBoxFlowSerial->currentData().toInt();

    m_options.networkLogs.address = m_ui->lineEditAddress->text();
    m_options.networkLogs.port = m_ui->lineEditPort->text().toUInt();

    m_options.save();
    accept();
}

void LogsOptionsDialog::initSerialPortOptions()
{
    SerialPortOptions& serialOptions = m_options.serialLogs;

    // Scan available serial ports.
    for(const QSerialPortInfo &info : QSerialPortInfo::availablePorts())
        m_ui->comboBoxPortSerial->addItem(info.portName(), info.description());

    QString defaultSerialLogsPort = serialOptions.portName;
    int findResult = m_ui->comboBoxPortSerial->findText(defaultSerialLogsPort);
    if(findResult != -1)
        m_ui->comboBoxPortSerial->setCurrentIndex(findResult);

    // Scan available baud rates.
    auto standardSpeeds = QSerialPortInfo::standardBaudRates();
    for(unsigned int speed : standardSpeeds)
        m_ui->comboBoxSpeedSerial->addItem(QString::number(speed), speed);

    unsigned int defaultSerialLogsSpeed = serialOptions.baudRate;
    findResult = m_ui->comboBoxSpeedSerial->findData(defaultSerialLogsSpeed);
    if(findResult != -1)
        m_ui->comboBoxSpeedSerial->setCurrentIndex(findResult);

    // Set possible data bits.
    m_ui->comboBoxDataBitsSerial->addItem(QString::number(QSerialPort::Data5), QSerialPort::Data5);
    m_ui->comboBoxDataBitsSerial->addItem(QString::number(QSerialPort::Data6), QSerialPort::Data6);
    m_ui->comboBoxDataBitsSerial->addItem(QString::number(QSerialPort::Data7), QSerialPort::Data7);
    m_ui->comboBoxDataBitsSerial->addItem(QString::number(QSerialPort::Data8), QSerialPort::Data8);

    unsigned int defaultSerialLogsDataBits = serialOptions.dataBits;
    findResult = m_ui->comboBoxDataBitsSerial->findData(defaultSerialLogsDataBits);
    if(findResult != -1)
        m_ui->comboBoxDataBitsSerial->setCurrentIndex(findResult);

    // Set possible stop bits.
    m_ui->comboBoxStopBitsSerial->addItem(QString::number(QSerialPort::OneStop), QSerialPort::OneStop);
    m_ui->comboBoxStopBitsSerial->addItem(QString::number(1.5), QSerialPort::OneAndHalfStop);
    m_ui->comboBoxStopBitsSerial->addItem(QString::number(QSerialPort::TwoStop), QSerialPort::TwoStop);

    unsigned int defaultSerialLogsStopBits = serialOptions.stopBits;
    findResult = m_ui->comboBoxStopBitsSerial->findData(defaultSerialLogsStopBits);
    if(findResult != -1)
        m_ui->comboBoxStopBitsSerial->setCurrentIndex(findResult);

    // Set possible bit partity.
    m_ui->comboBoxPartitySerial->addItem("None", QSerialPort::NoParity);
    m_ui->comboBoxPartitySerial->addItem("Even", QSerialPort::EvenParity);
    m_ui->comboBoxPartitySerial->addItem("Odd", QSerialPort::OddParity);
    m_ui->comboBoxPartitySerial->addItem("Space", QSerialPort::SpaceParity);
    m_ui->comboBoxPartitySerial->addItem("Mark", QSerialPort::MarkParity);

    unsigned int defaultSerialLogsPartity = serialOptions.partity;
    findResult = m_ui->comboBoxPartitySerial->findData(defaultSerialLogsPartity);
    if(findResult != -1)
        m_ui->comboBoxPartitySerial->setCurrentIndex(findResult);

    // Set possible flow control.
    m_ui->comboBoxFlowSerial->addItem("None", QSerialPort::NoFlowControl);
    m_ui->comboBoxFlowSerial->addItem("RTS/CTS", QSerialPort::HardwareControl);
    m_ui->comboBoxFlowSerial->addItem("XON/XOFF", QSerialPort::SoftwareControl);

    unsigned int defaultSerialLogsFlow = serialOptions.flowControl;
    findResult = m_ui->comboBoxFlowSerial->findData(defaultSerialLogsFlow);
    if(findResult != -1)
        m_ui->comboBoxFlowSerial->setCurrentIndex(findResult);
}

void LogsOptionsDialog::initNetworkOptions()
{
    NetworkServerOptions& serverOptions = m_options.networkLogs;

    m_ui->lineEditAddress->setText(serverOptions.address);
    m_ui->lineEditPort->setText(QString::number(serverOptions.port));
}
