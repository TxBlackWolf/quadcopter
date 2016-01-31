////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       28.11.2015
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef LOGSOPTIONSDIALOG_H
#define LOGSOPTIONSDIALOG_H

#include "Tools/Options/LogsOptions.h"

#include <QDialog>

namespace Ui {
    class LogsOptionsDialog;
}

class LogsOptionsDialog : public QDialog {
    Q_OBJECT

public:
    explicit LogsOptionsDialog(QWidget* parent = 0);
    virtual ~LogsOptionsDialog();

public slots:
    void changeSerialLogsPortInfo(int currentPortIndex);
    void radioButtonSerialToggled(bool state);
    void radioButtonNetworkToggled(bool state);
    void buttonSelectLogsDirClicked();
    void saveOptions();



private:
    void init();
    void initSerialPortOptions();
    void initNetworkOptions();

private:
    Ui::LogsOptionsDialog* m_ui;

    LogsOptions m_options;
};

#endif
