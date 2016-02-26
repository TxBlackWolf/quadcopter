////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       08.02.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "EmulatorWidget.h"
#include "ui_EmulatorWidget.h"

#include "common/commands/commands.h"
#include "common/commands/emulator.h"
#include "Tools/Options/EmulatorOptions.h"

#include <string>

static EmulatorWidget* globalEmulatorWidget = nullptr;

EmulatorWidget::EmulatorWidget(QWidget* parent)
    : QWidget(parent)
    , m_ui(new Ui::EmulatorWidget())
    , m_socket(nullptr)
{
    m_ui->setupUi(this);
    init();

    globalEmulatorWidget = this;
}

EmulatorWidget::~EmulatorWidget()
{
    delete m_ui;
}

void EmulatorWidget::startEmulatorServer()
{
    EmulatorOptions options;
    options.load();

    // This is non-blocking call.
    if(!m_tcpServer.listen(QHostAddress::Any, options.emulatorServer.port))
        return;

    disconnect(m_ui->buttonStart, SIGNAL(clicked()), this, SLOT(startEmulatorServer()));
    connect(m_ui->buttonStart, SIGNAL(clicked()), this, SLOT(stopEmulatorServer()));
    m_ui->buttonStart->setText("Stop");

    emit emulatorStatus(SubsystemStatus_t::SUBSYSTEM_ENABLED);
}

void EmulatorWidget::stopEmulatorServer()
{
    disconnect(m_ui->buttonStart, SIGNAL(clicked()), this, SLOT(stopEmulatorServer()));
    connect(m_ui->buttonStart, SIGNAL(clicked()), this, SLOT(startEmulatorServer()));
    m_ui->buttonStart->setText("Start");

    if(m_socket) {
        disconnect(m_socket, SIGNAL(readyRead()), this, SLOT(readSocket()));
        disconnect(m_socket, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
        m_socket->close();
        m_socket = nullptr;
    }

    if(m_tcpServer.isListening())
        m_tcpServer.close();

    emit emulatorStatus(SubsystemStatus_t::SUBSYSTEM_DISABLED);
}

void EmulatorWidget::accept()
{
    m_socket = m_tcpServer.nextPendingConnection();
    if(!m_socket)
        return;

    connect(m_socket, SIGNAL(readyRead()), this, SLOT(readSocket()));
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));

    // We accept only one client.
    m_tcpServer.close();

    emit emulatorStatus(SubsystemStatus_t::SUBSYSTEM_CONNECTED);
}

void EmulatorWidget::readSocket()
{
    QTcpSocket* socket = dynamic_cast<QTcpSocket*>(sender());
    std::string message = socket->readAll().toStdString();
    uint8_t* data = reinterpret_cast<uint8_t *>(const_cast<char *>(message.data()));

    command_parse(data);
}

void EmulatorWidget::clientDisconnected()
{
    disconnect(m_socket, SIGNAL(readyRead()), this, SLOT(readSocket()));
    disconnect(m_socket, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
    m_socket = nullptr;

    emit emulatorStatus(SubsystemStatus_t::SUBSYSTEM_ENABLED);

    EmulatorOptions options;
    options.load();
    m_tcpServer.listen(QHostAddress::Any, options.emulatorServer.port);
}

void EmulatorWidget::init()
{
    connect(m_ui->buttonStart, SIGNAL(clicked()), this, SLOT(startEmulatorServer()));

    initCommandsFramework();
}

void EmulatorWidget::initCommandsFramework()
{
    command_registerEmulatorCallback(EMULATED_DEVICE_GPIO, &EmulatorWidget::gpioCallback);
}

void EmulatorWidget::gpioCallback(uint8_t* buffer, uint32_t size)
{
    /// @todo: Implement.
}
