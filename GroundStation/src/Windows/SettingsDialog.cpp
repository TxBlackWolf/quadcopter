////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       20.02.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "SettingsDialog.h"
#include "Tools/Options/ServerOptions.h"
#include "ui_SettingsDialog.h"

#include <QFileDialog>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

SettingsDialog::SettingsDialog(QWidget* parent)
    : QDialog(parent)
    , m_ui(new Ui::SettingsDialog)
    , m_logsStarted(false)
{
    m_ui->setupUi(this);

    init();
}

SettingsDialog::~SettingsDialog()
{
    delete m_ui;
}

void SettingsDialog::init()
{
    connect(m_ui->buttonBox, SIGNAL(accepted()), this, SLOT(saveSettings()));
    connect(m_ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    initLogsSettings();
}

void SettingsDialog::changeSerialLogsPortInfo(int currentPortIndex)
{
    QString portDescription = m_ui->comboSerialPortLogs->itemData(currentPortIndex).toString();
    m_ui->labelPortDescLogs->setText(portDescription);
}

void SettingsDialog::radioSerialLogsToggled(bool state)
{
    m_ui->radioSerialLogs->setChecked(state);
    m_ui->comboSerialPortLogs->setEnabled(state);
    m_ui->comboSpeedLogs->setEnabled(state);
    m_ui->comboDataBitsLogs->setEnabled(state);
    m_ui->comboStopBitsLogs->setEnabled(state);
    m_ui->comboPartityLogs->setEnabled(state);
    m_ui->comboFlowLogs->setEnabled(state);
}

void SettingsDialog::radioNetworkLogsToggled(bool state)
{
    m_ui->radioNetworkLogs->setChecked(state);
    m_ui->editAddressLogs->setEnabled(state);
    m_ui->editPortLogs->setEnabled(state);
}

void SettingsDialog::buttonSelectLogsDirClicked()
{
    QString logsPath = QFileDialog::getExistingDirectory(this, "Save logs to");
    m_ui->editLogsDir->setText(logsPath);
}

void SettingsDialog::buttonStartLogsClicked()
{
    saveSettings();

    m_logsStarted = !m_logsStarted;
    emit logsStarted(m_logsStarted);

    QString imageResource = m_logsStarted ? ":/Icons/Icons/power-button-red.png" : ":/Icons/Icons/power-button-green.png";
    m_ui->buttonStartLogs->setIcon(QIcon(QPixmap(imageResource)));

    QString buttonText = m_logsStarted ? "Stop" : "Start";
    m_ui->buttonStartLogs->setText(buttonText);
}

void SettingsDialog::saveSettings()
{
    saveLogsSettings();
    accept();
}

void SettingsDialog::initLogsSettings()
{
    connect(m_ui->comboSerialPortLogs, SIGNAL(currentIndexChanged(int)), this, SLOT(changeSerialLogsPortInfo(int)));
    connect(m_ui->radioSerialLogs, SIGNAL(toggled(bool)), this, SLOT(radioSerialLogsToggled(bool)));
    connect(m_ui->radioNetworkLogs, SIGNAL(toggled(bool)), this, SLOT(radioNetworkLogsToggled(bool)));
    connect(m_ui->pushButtonLogsDir, SIGNAL(clicked()), this, SLOT(buttonSelectLogsDirClicked()));
    connect(m_ui->buttonStartLogs, SIGNAL(clicked()), this, SLOT(buttonStartLogsClicked()));

    m_optionsLogs.load();

    SerialPortOptions& serialOptions = m_optionsLogs.serverOptions.serialServer;
    initSerialPortsCombo(m_ui->comboSerialPortLogs, serialOptions.portName);
    initSpeedCombo(m_ui->comboSpeedLogs, serialOptions.baudRate);
    initDataBitsCombo(m_ui->comboDataBitsLogs, serialOptions.dataBits);
    initStopBitsCombo(m_ui->comboStopBitsLogs, serialOptions.stopBits);
    initPartityCombo(m_ui->comboPartityLogs, serialOptions.partity);
    initFlowControlCombo(m_ui->comboFlowLogs, serialOptions.flowControl);

    TCPOptions& networkOptions = m_optionsLogs.serverOptions.tcpServer;
    m_ui->editAddressLogs->setText(networkOptions.address);
    m_ui->editPortLogs->setText(QString::number(networkOptions.port));

    m_ui->editLogsDir->setText(m_optionsLogs.logsPath);

    bool selectSerialLogs = m_optionsLogs.serverOptions.serverType == ServerOptions::SERVER_SERIAL;
    radioSerialLogsToggled(selectSerialLogs);
    radioNetworkLogsToggled(!selectSerialLogs);
}

void SettingsDialog::initSerialPortsCombo(QComboBox* comboBox, QString defaultPort)
{
    // Scan available serial ports.
    for(const QSerialPortInfo &info : QSerialPortInfo::availablePorts())
        comboBox->addItem(info.portName(), info.description());

    int defaultIndex = comboBox->findText(defaultPort);
    if(defaultIndex != -1)
        comboBox->setCurrentIndex(defaultIndex);
}

void SettingsDialog::initSpeedCombo(QComboBox* comboBox, unsigned int defaultSpeed)
{
    // Scan available baud rates.
    auto standardSpeeds = QSerialPortInfo::standardBaudRates();
    for(unsigned int speed : standardSpeeds)
        comboBox->addItem(QString::number(speed), speed);

    int defaultIndex = comboBox->findData(defaultSpeed);
    if(defaultIndex != -1)
        comboBox->setCurrentIndex(defaultIndex);
}

void SettingsDialog::initDataBitsCombo(QComboBox* comboBox, unsigned int defaultDataBits)
{
    // Set possible data bits.
    comboBox->addItem(QString::number(QSerialPort::Data5), QSerialPort::Data5);
    comboBox->addItem(QString::number(QSerialPort::Data6), QSerialPort::Data6);
    comboBox->addItem(QString::number(QSerialPort::Data7), QSerialPort::Data7);
    comboBox->addItem(QString::number(QSerialPort::Data8), QSerialPort::Data8);

    int defaultIndex = comboBox->findData(defaultDataBits);
    if(defaultIndex != -1)
        comboBox->setCurrentIndex(defaultIndex);
}

void SettingsDialog::initStopBitsCombo(QComboBox* comboBox, unsigned int defaultStopBits)
{
    // Set possible stop bits.
    comboBox->addItem(QString::number(QSerialPort::OneStop), QSerialPort::OneStop);
    comboBox->addItem(QString::number(1.5), QSerialPort::OneAndHalfStop);
    comboBox->addItem(QString::number(QSerialPort::TwoStop), QSerialPort::TwoStop);

    int defaultIndex = comboBox->findData(defaultStopBits);
    if(defaultIndex != -1)
        comboBox->setCurrentIndex(defaultIndex);
}

void SettingsDialog::initPartityCombo(QComboBox* comboBox, unsigned int defaultPartity)
{
    // Set possible bit partity.
    comboBox->addItem("None", QSerialPort::NoParity);
    comboBox->addItem("Even", QSerialPort::EvenParity);
    comboBox->addItem("Odd", QSerialPort::OddParity);
    comboBox->addItem("Space", QSerialPort::SpaceParity);
    comboBox->addItem("Mark", QSerialPort::MarkParity);

    int defaultIndex = comboBox->findData(defaultPartity);
    if(defaultIndex != -1)
        comboBox->setCurrentIndex(defaultIndex);
}

void SettingsDialog::initFlowControlCombo(QComboBox* comboBox, unsigned int defaultFlow)
{
    // Set possible flow control.
    comboBox->addItem("None", QSerialPort::NoFlowControl);
    comboBox->addItem("RTS/CTS", QSerialPort::HardwareControl);
    comboBox->addItem("XON/XOFF", QSerialPort::SoftwareControl);

    int defaultIndex = comboBox->findData(defaultFlow);
    if(defaultIndex != -1)
        comboBox->setCurrentIndex(defaultIndex);
}

void SettingsDialog::saveLogsSettings()
{
    m_optionsLogs.load();

    m_optionsLogs.serverOptions.serverType = m_ui->radioSerialLogs->isChecked() ? ServerOptions::SERVER_SERIAL : ServerOptions::SERVER_TCP;
    m_optionsLogs.logsPath = m_ui->editLogsDir->text();

    SerialPortOptions& serialOptions = m_optionsLogs.serverOptions.serialServer;
    serialOptions.portName = m_ui->comboSerialPortLogs->currentText();
    serialOptions.baudRate = m_ui->comboSpeedLogs->currentData().toInt();
    serialOptions.dataBits = (QSerialPort::DataBits) m_ui->comboDataBitsLogs->currentData().toInt();
    serialOptions.stopBits = (QSerialPort::StopBits) m_ui->comboStopBitsLogs->currentData().toInt();
    serialOptions.partity = (QSerialPort::Parity) m_ui->comboPartityLogs->currentData().toInt();
    serialOptions.flowControl = (QSerialPort::FlowControl) m_ui->comboFlowLogs->currentData().toInt();

    TCPOptions& networkOptions = m_optionsLogs.serverOptions.tcpServer;
    networkOptions.address = m_ui->editAddressLogs->text();
    networkOptions.port = m_ui->editPortLogs->text().toUInt();

    m_optionsLogs.save();
}
