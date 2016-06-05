////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       20.02.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include "Core/SteeringController.h"
#include "Tools/Options/CommandsOptions.h"
#include "Tools/Options/LogsOptions.h"

#include <QComboBox>
#include <QDialog>
#include <QString>

namespace Ui {
    class SettingsDialog;
}

class SettingsDialog : public QDialog {
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget* parent = nullptr);
    virtual ~SettingsDialog();

signals:
    void logsStarted(bool state);
    void commandsStarted(bool state);
    void connectPadController(QString device);
    void padSensitivityChanged(int value);
    void assignKeys(bool enabled);
    void registerAxisEvent(int id, SteeringController::AxisSteeringEvent type);
    void registerButtonEvent(int id, SteeringController::ButtonSteeringEvent type);

public slots:
    void changeSerialLogsPortInfo(int currentPortIndex);
    void changeSerialCommandsPortInfo(int currentPortIndex);
    void radioSerialLogsToggled(bool state);
    void radioSerialCommandsToggled(bool state);
    void radioNetworkLogsToggled(bool state);
    void radioNetworkCommandsToggled(bool state);
    void buttonSelectLogsDirClicked();
    void buttonStartLogsClicked();
    void buttonStartCommandsClicked();
    void buttonStartAllClicked();
    void buttonConnectPadControllerClicked();
    void setButtonAll();
    void setPadControllerName(QString name);
    void setPadSensitivity(int value);
    void buttonAssignClicked();
    void buttonClearClicked();
    void setPadAxisMapping(int id, int);
    void setPadButtonMapping(int id, bool);

    void saveSettings();

private:
    void init();
    void initLogsSettings();
    void initCommandsSettings();
    void initPadControllerSettings();

    void initSerialPortsCombo(QComboBox* comboBox, QString defaultPort);
    void initSpeedCombo(QComboBox* comboBox, unsigned int defaultSpeed);
    void initDataBitsCombo(QComboBox* comboBox, unsigned int defaultDataBits);
    void initStopBitsCombo(QComboBox* comboBox, unsigned int defaultStopBits);
    void initPartityCombo(QComboBox* comboBox, unsigned int defaultPartity);
    void initFlowControlCombo(QComboBox* comboBox, unsigned int defaultFlowControl);
    void initInputDeviceCombo(QComboBox* comboBox);
    void registerKeyForEvent(int keyId);

    void saveLogsSettings();
    void saveCommandsSettings();

private:
    Ui::SettingsDialog* m_ui;

    LogsOptions m_optionsLogs;
    CommandsOptions m_optionsCommands;

    bool m_keyAssigning;
    bool m_logsStarted;
    bool m_commandsStarted;
    bool m_padControllerConnected;
    bool m_allToBeStarted;
};

#endif
