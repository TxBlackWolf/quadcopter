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
#include "Core/PadCalibrator.h"
#include "Tools/Options/Common/ServerOptions.h"
#include "ui_SettingsDialog.h"

#include <QDirIterator>
#include <QFileDialog>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

SettingsDialog::SettingsDialog(QWidget* parent)
    : QDialog(parent)
    , m_ui(new Ui::SettingsDialog)
    , m_keyAssigning(false)
    , m_logsStarted(false)
    , m_commandsStarted(false)
    , m_padControllerConnected(false)
    , m_allToBeStarted(true)
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
    connect(m_ui->buttonStartAll, SIGNAL(clicked()), this, SLOT(buttonStartAllClicked()));
    connect(m_ui->sliderSensitivity, SIGNAL(valueChanged(int)), this, SLOT(setPadSensitivity(int)));
    connect(m_ui->buttonAssign, SIGNAL(clicked()), this, SLOT(buttonAssignClicked()));
    connect(m_ui->buttonClear, SIGNAL(clicked()), this, SLOT(buttonClearClicked()));

    initLogsSettings();
    initCommandsSettings();
    initPadControllerSettings();
}

void SettingsDialog::changeSerialLogsPortInfo(int currentPortIndex)
{
    QString portDescription = m_ui->comboSerialPortLogs->itemData(currentPortIndex).toString();
    m_ui->labelPortDescLogs->setText(portDescription);
}

void SettingsDialog::changeSerialCommandsPortInfo(int currentPortIndex)
{
    QString portDescription = m_ui->comboSerialPortCommands->itemData(currentPortIndex).toString();
    m_ui->labelPortDescCommands->setText(portDescription);
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

void SettingsDialog::radioSerialCommandsToggled(bool state)
{
    m_ui->radioSerialCommands->setChecked(state);
    m_ui->comboSerialPortCommands->setEnabled(state);
    m_ui->comboSpeedCommands->setEnabled(state);
    m_ui->comboDataBitsCommands->setEnabled(state);
    m_ui->comboStopBitsCommands->setEnabled(state);
    m_ui->comboPartityCommands->setEnabled(state);
    m_ui->comboFlowCommands->setEnabled(state);
}

void SettingsDialog::radioNetworkLogsToggled(bool state)
{
    m_ui->radioNetworkLogs->setChecked(state);
    m_ui->editAddressLogs->setEnabled(state);
    m_ui->editPortLogs->setEnabled(state);
}

void SettingsDialog::radioNetworkCommandsToggled(bool state)
{
    m_ui->radioNetworkCommands->setChecked(state);
    m_ui->editAddressCommands->setEnabled(state);
    m_ui->editPortCommands->setEnabled(state);
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

void SettingsDialog::buttonStartCommandsClicked()
{
    saveSettings();

    m_commandsStarted = !m_commandsStarted;
    emit commandsStarted(m_commandsStarted);

    QString imageResource = m_commandsStarted ? ":/Icons/Icons/power-button-red.png" : ":/Icons/Icons/power-button-green.png";
    m_ui->buttonStartCommands->setIcon(QIcon(QPixmap(imageResource)));

    QString buttonText = m_commandsStarted ? "Stop" : "Start";
    m_ui->buttonStartCommands->setText(buttonText);
}

void SettingsDialog::buttonStartAllClicked()
{
    if(m_allToBeStarted != m_logsStarted)
        buttonStartLogsClicked();

    if(m_allToBeStarted != m_commandsStarted)
        buttonStartCommandsClicked();

    setButtonAll();
}

void SettingsDialog::buttonConnectPadControllerClicked()
{
    saveSettings();

    m_padControllerConnected = !m_padControllerConnected;
    emit connectPadController(m_ui->comboPadDevice->currentText());

    QString imageResource = m_padControllerConnected ? ":/Icons/Icons/power-button-red.png" : ":/Icons/Icons/power-button-green.png";
    m_ui->buttonConnectPad->setIcon(QIcon(QPixmap(imageResource)));

    QString buttonText = m_padControllerConnected ? "Stop" : "Start";
    m_ui->buttonConnectPad->setText(buttonText);
}

void SettingsDialog::setButtonAll()
{
    if(m_allToBeStarted && !(m_logsStarted && m_commandsStarted))
        return;

    if(!m_allToBeStarted && (m_logsStarted || m_commandsStarted))
        return;

    if(m_allToBeStarted && m_logsStarted && m_commandsStarted)
        m_allToBeStarted = false;
    else if(!m_allToBeStarted && !m_logsStarted && !m_commandsStarted)
        m_allToBeStarted = true;

    QString imageResourceAll = m_allToBeStarted ? ":/Icons/Icons/power-button-green.png" : ":/Icons/Icons/power-button-red.png";
    m_ui->buttonStartAll->setIcon(QIcon(QPixmap(imageResourceAll)));

    QString buttonTextAll = m_allToBeStarted ? "Start All" : "Stop All";
    m_ui->buttonStartAll->setText(buttonTextAll);
}

void SettingsDialog::setPadControllerName(QString name)
{
    m_ui->labelPadName->setText(name);
}

void SettingsDialog::setPadSensitivity(int value)
{
    m_ui->labelSensitivityPerc->setText(QString::number(value) + " %");
    emit padSensitivityChanged(value);
}

void SettingsDialog::buttonAssignClicked()
{
    m_keyAssigning = !m_keyAssigning;

    m_ui->keyThrottle->setEnabled(m_keyAssigning);
    m_ui->keyRotate->setEnabled(m_keyAssigning);
    m_ui->keyFrontBack->setEnabled(m_keyAssigning);
    m_ui->keyLeftRight->setEnabled(m_keyAssigning);
    m_ui->keyLandingGear->setEnabled(m_keyAssigning);
    m_ui->keyMainLights->setEnabled(m_keyAssigning);
    m_ui->keyBottomLights->setEnabled(m_keyAssigning);
    m_ui->keyReturnBase->setEnabled(m_keyAssigning);
    m_ui->keyFunc9->setEnabled(m_keyAssigning);
    m_ui->keyFunc10->setEnabled(m_keyAssigning);
    m_ui->keyFunc11->setEnabled(m_keyAssigning);
    m_ui->keyFunc12->setEnabled(m_keyAssigning);
    m_ui->keyFunc13->setEnabled(m_keyAssigning);
    m_ui->keyFunc14->setEnabled(m_keyAssigning);
    m_ui->keyFunc15->setEnabled(m_keyAssigning);
    m_ui->keyFunc16->setEnabled(m_keyAssigning);

    m_ui->keyThrottle->setClearButtonEnabled(m_keyAssigning);
    m_ui->keyRotate->setClearButtonEnabled(m_keyAssigning);
    m_ui->keyFrontBack->setClearButtonEnabled(m_keyAssigning);
    m_ui->keyLeftRight->setClearButtonEnabled(m_keyAssigning);
    m_ui->keyLandingGear->setClearButtonEnabled(m_keyAssigning);
    m_ui->keyMainLights->setClearButtonEnabled(m_keyAssigning);
    m_ui->keyBottomLights->setClearButtonEnabled(m_keyAssigning);
    m_ui->keyReturnBase->setClearButtonEnabled(m_keyAssigning);
    m_ui->keyFunc9->setClearButtonEnabled(m_keyAssigning);
    m_ui->keyFunc10->setClearButtonEnabled(m_keyAssigning);
    m_ui->keyFunc11->setClearButtonEnabled(m_keyAssigning);
    m_ui->keyFunc12->setClearButtonEnabled(m_keyAssigning);
    m_ui->keyFunc13->setClearButtonEnabled(m_keyAssigning);
    m_ui->keyFunc14->setClearButtonEnabled(m_keyAssigning);
    m_ui->keyFunc15->setClearButtonEnabled(m_keyAssigning);
    m_ui->keyFunc16->setClearButtonEnabled(m_keyAssigning);

    m_ui->keyThrottle->setFocus();

    emit assignKeys(m_keyAssigning);
}

void SettingsDialog::buttonClearClicked()
{
    m_ui->keyThrottle->clear();
    m_ui->keyRotate->clear();
    m_ui->keyFrontBack->clear();
    m_ui->keyLeftRight->clear();
    m_ui->keyLandingGear->clear();
    m_ui->keyMainLights->clear();
    m_ui->keyBottomLights->clear();
    m_ui->keyReturnBase->clear();
    m_ui->keyFunc9->clear();
    m_ui->keyFunc10->clear();
    m_ui->keyFunc11->clear();
    m_ui->keyFunc12->clear();
    m_ui->keyFunc13->clear();
    m_ui->keyFunc14->clear();
    m_ui->keyFunc15->clear();
    m_ui->keyFunc16->clear();
}

void SettingsDialog::setPadAxisMapping(int id, int)
{
    if(!isVisible())
        return;

    if(!focusWidget()->objectName().startsWith("key"))
        return;

    QLineEdit *lineEdit = dynamic_cast<QLineEdit *>(focusWidget());
    if(!lineEdit)
        return;

    lineEdit->setText(IPadCalibrator::getAxisName(id));
}

void SettingsDialog::setPadButtonMapping(int id, int)
{
    if(!isVisible())
        return;

    if(!focusWidget()->objectName().startsWith("key"))
        return;

    QLineEdit *lineEdit = dynamic_cast<QLineEdit *>(focusWidget());
    if(!lineEdit)
        return;

    lineEdit->setText(IPadCalibrator::getButtonName(id));
}

void SettingsDialog::saveSettings()
{
    saveLogsSettings();
    saveCommandsSettings();
    accept();
}

void SettingsDialog::initLogsSettings()
{
    connect(m_ui->comboSerialPortLogs, SIGNAL(currentIndexChanged(int)), this, SLOT(changeSerialLogsPortInfo(int)));
    connect(m_ui->radioSerialLogs, SIGNAL(toggled(bool)), this, SLOT(radioSerialLogsToggled(bool)));
    connect(m_ui->radioNetworkLogs, SIGNAL(toggled(bool)), this, SLOT(radioNetworkLogsToggled(bool)));
    connect(m_ui->pushButtonLogsDir, SIGNAL(clicked()), this, SLOT(buttonSelectLogsDirClicked()));
    connect(m_ui->buttonStartLogs, SIGNAL(clicked()), this, SLOT(buttonStartLogsClicked()));
    connect(m_ui->buttonStartLogs, SIGNAL(clicked()), this, SLOT(setButtonAll()));

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

void SettingsDialog::initCommandsSettings()
{
    connect(m_ui->comboSerialPortCommands, SIGNAL(currentIndexChanged(int)), this, SLOT(changeSerialCommandsPortInfo(int)));
    connect(m_ui->radioSerialCommands, SIGNAL(toggled(bool)), this, SLOT(radioSerialCommandsToggled(bool)));
    connect(m_ui->radioNetworkCommands, SIGNAL(toggled(bool)), this, SLOT(radioNetworkCommandsToggled(bool)));
    connect(m_ui->buttonStartCommands, SIGNAL(clicked()), this, SLOT(buttonStartCommandsClicked()));
    connect(m_ui->buttonStartCommands, SIGNAL(clicked()), this, SLOT(setButtonAll()));

    m_optionsCommands.load();

    SerialPortOptions& serialOptions = m_optionsCommands.serverOptions.serialServer;
    initSerialPortsCombo(m_ui->comboSerialPortCommands, serialOptions.portName);
    initSpeedCombo(m_ui->comboSpeedCommands, serialOptions.baudRate);
    initDataBitsCombo(m_ui->comboDataBitsCommands, serialOptions.dataBits);
    initStopBitsCombo(m_ui->comboStopBitsCommands, serialOptions.stopBits);
    initPartityCombo(m_ui->comboPartityCommands, serialOptions.partity);
    initFlowControlCombo(m_ui->comboFlowCommands, serialOptions.flowControl);

    TCPOptions& networkOptions = m_optionsCommands.serverOptions.tcpServer;
    m_ui->editAddressCommands->setText(networkOptions.address);
    m_ui->editPortCommands->setText(QString::number(networkOptions.port));

    bool selectSerialCommands = m_optionsCommands.serverOptions.serverType == ServerOptions::SERVER_SERIAL;
    radioSerialCommandsToggled(selectSerialCommands);
    radioNetworkCommandsToggled(!selectSerialCommands);
}

void SettingsDialog::initPadControllerSettings()
{
    connect(m_ui->buttonConnectPad, SIGNAL(clicked()), this, SLOT(buttonConnectPadControllerClicked()));

    initInputDeviceCombo(m_ui->comboPadDevice);
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

void SettingsDialog::initInputDeviceCombo(QComboBox* comboBox)
{
    QDirIterator it("/dev/input",  QStringList() << "js*", QDir::System);
    while(it.hasNext())
        comboBox->addItem(it.next());
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

void SettingsDialog::saveCommandsSettings()
{
    m_optionsCommands.load();

    m_optionsCommands.serverOptions.serverType = m_ui->radioSerialCommands->isChecked() ? ServerOptions::SERVER_SERIAL : ServerOptions::SERVER_TCP;

    SerialPortOptions& serialOptions = m_optionsCommands.serverOptions.serialServer;
    serialOptions.portName = m_ui->comboSerialPortCommands->currentText();
    serialOptions.baudRate = m_ui->comboSpeedCommands->currentData().toInt();
    serialOptions.dataBits = (QSerialPort::DataBits) m_ui->comboDataBitsCommands->currentData().toInt();
    serialOptions.stopBits = (QSerialPort::StopBits) m_ui->comboStopBitsCommands->currentData().toInt();
    serialOptions.partity = (QSerialPort::Parity) m_ui->comboPartityCommands->currentData().toInt();
    serialOptions.flowControl = (QSerialPort::FlowControl) m_ui->comboFlowCommands->currentData().toInt();

    TCPOptions& networkOptions = m_optionsCommands.serverOptions.tcpServer;
    networkOptions.address = m_ui->editAddressCommands->text();
    networkOptions.port = m_ui->editPortCommands->text().toUInt();

    m_optionsCommands.save();
}
