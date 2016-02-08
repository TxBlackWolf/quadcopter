////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       08.02.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef EMULATOROPTIONSDIALOG_H
#define EMULATOROPTIONSDIALOG_H

#include "Tools/Options/EmulatorOptions.h"

#include <QDialog>

namespace Ui {
    class EmulatorOptionsDialog;
}

class EmulatorOptionsDialog : public QDialog {
    Q_OBJECT

public:
    explicit EmulatorOptionsDialog(QWidget* parent = 0);
    virtual ~EmulatorOptionsDialog();

public slots:
    void saveOptions();

private:
    void init();
    void initEmulatorOptions();

private:
    Ui::EmulatorOptionsDialog* m_ui;

    EmulatorOptions m_options;
};

#endif
