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

#include "Tools/Options/LogsOptions.h"

#include <QComboBox>
#include <QDialog>

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

public slots:
    void changeSerialLogsPortInfo(int currentPortIndex);
    void radioSerialLogsToggled(bool state);
    void radioNetworkLogsToggled(bool state);
    void buttonSelectLogsDirClicked();
    void buttonStartLogsClicked();

    void saveSettings();

private:
    void init();
    void initLogsSettings();

    void initSerialPortsCombo(QComboBox* comboBox, QString defaultPort);
    void initSpeedCombo(QComboBox* comboBox, unsigned int defaultSpeed);
    void initDataBitsCombo(QComboBox* comboBox, unsigned int defaultDataBits);
    void initStopBitsCombo(QComboBox* comboBox, unsigned int defaultStopBits);
    void initPartityCombo(QComboBox* comboBox, unsigned int defaultPartity);
    void initFlowControlCombo(QComboBox* comboBox, unsigned int defaultFlowControl);

    void saveLogsSettings();

private:
    Ui::SettingsDialog* m_ui;

    LogsOptions m_optionsLogs;

    bool m_logsStarted;
};

#endif
