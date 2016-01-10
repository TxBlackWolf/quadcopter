//============================================================================
//
// Filename   : LogsOptionsDialog.h
// Author     : Kuba Sejdak
// Created on : 28 lis 2014
//
//============================================================================

#ifndef LOGSOPTIONSDIALOG_H
#define LOGSOPTIONSDIALOG_H

#include <QDialog>

namespace Ui
{
    class LogsOptionsDialog;
}

class LogsOptionsDialog : public QDialog
{
    Q_OBJECT

public:
    /// @brief Constructor.
    /// @param [in] parent              parent widget
    explicit LogsOptionsDialog(QWidget* parent = 0);

    /// @brief Virtual destructor.
    virtual ~LogsOptionsDialog();

public slots:
    /// @brief Updates description for currently selected serial port.
    /// @param [in] currentPortIndex    index of current port
    void changeSerialLogsPortInfo(int currentPortIndex);

    /// @brief Updates description for currently selected radio port.
    /// @param [in] currentPortIndex    index of current port
    void changeRadioLogsPortInfo(int currentPortIndex);

    /// @brief Saves all current options.
    void saveOptions();



private:
    /// @brief Initializes options dialog.
    void init();

    /// @brief Initializes all options related to serial ports.
    void initSerialPortOptions();

private:
    Ui::LogsOptionsDialog* m_ui;
};

#endif
