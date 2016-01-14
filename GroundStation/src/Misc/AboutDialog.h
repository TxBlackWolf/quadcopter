//=============================================================================================
//
// Filename   : AboutDialog.h
// Author     : Kuba Sejdak
// Created on : 29.11.2014
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//=============================================================================================

#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>

namespace Ui {
    class AboutDialog;
}

class AboutDialog : public QDialog {
    Q_OBJECT

public:
    /// @brief Constructor.
    /// @param [in] parent      parent widget
    explicit AboutDialog(QWidget* parent = 0);

    /// @brief Virtual destructor.
    ~AboutDialog();

private:
    Ui::AboutDialog* m_ui;
};

#endif
