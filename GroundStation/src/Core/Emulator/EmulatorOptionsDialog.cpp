////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       08.02.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "EmulatorOptionsDialog.h"
#include "ui_EmulatorOptionsDialog.h"

EmulatorOptionsDialog::EmulatorOptionsDialog(QWidget* parent)
    : QDialog(parent)
    , m_ui(new Ui::EmulatorOptionsDialog())
{
    m_ui->setupUi(this);

    init();
}

EmulatorOptionsDialog::~EmulatorOptionsDialog()
{
    delete m_ui;
}

void EmulatorOptionsDialog::init()
{
    connect(m_ui->buttonBox, SIGNAL(accepted()), this, SLOT(saveOptions()));
    connect(m_ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    m_options.load();

    initEmulatorOptions();
}

void EmulatorOptionsDialog::saveOptions()
{
    m_options.load();

    m_options.emulatorServer.address = m_ui->lineEditAddress->text();
    m_options.emulatorServer.port = m_ui->lineEditPort->text().toUInt();

    m_options.save();
    accept();
}

void EmulatorOptionsDialog::initEmulatorOptions()
{
    NetworkServerOptions& serverOptions = m_options.emulatorServer;

    m_ui->lineEditAddress->setText(serverOptions.address);
    m_ui->lineEditPort->setText(QString::number(serverOptions.port));
}
