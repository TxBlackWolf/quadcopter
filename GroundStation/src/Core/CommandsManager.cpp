////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       09.04.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "CommandsManager.h"
#include "command/command_common.h"
#include "command/command_decoder.h"
#include "Tools/Options/CommandsOptions.h"

#include <functional>

using namespace std::placeholders;

CommandsManager::CommandsManager()
{
    init();
}

CommandsManager::~CommandsManager()
{
    try {
        delete [] m_buffer;
        setOperating(false);
    }
    catch(...) {}
}

void CommandsManager::setOperating(bool activate)
{
    if(!activate && m_server) {
        m_server->stop();
        m_server.release();
        emit geolocationStatus(SubsystemStatus::SUBSYSTEM_DISABLED);
        emit telemetryStatus(SubsystemStatus::SUBSYSTEM_DISABLED);
        emit fpvStatus(SubsystemStatus::SUBSYSTEM_DISABLED);
        emit steeringStatus(SubsystemStatus::SUBSYSTEM_DISABLED);
        emit emulatorStatus(SubsystemStatus::SUBSYSTEM_DISABLED);
        return;
    }

    CommandsOptions options;
    options.load();
    m_server.reset(IServer::create(options.serverOptions.serverType));
    m_server->setOnMessageCallback(std::bind(&CommandsManager::parseCommand, this, _1));
    m_server->setOnClientDisconnectedCallback(std::bind(&CommandsManager::commandSessionClosed, this, _1));

    if(!m_server->start(options.serverOptions))
        return;

    emit geolocationStatus(SubsystemStatus::SUBSYSTEM_ENABLED);
    emit telemetryStatus(SubsystemStatus::SUBSYSTEM_ENABLED);
    emit fpvStatus(SubsystemStatus::SUBSYSTEM_ENABLED);
    emit steeringStatus(SubsystemStatus::SUBSYSTEM_ENABLED);
    emit emulatorStatus(SubsystemStatus::SUBSYSTEM_ENABLED);
}

void CommandsManager::init()
{
    m_buffer = new uint8_t[2 * COMMAND_MAX_SIZE_BYTES];
    commandDecoder_init(m_buffer);
}

void CommandsManager::parseCommand(const QByteArray& command)
{
    const uint8_t* data = reinterpret_cast<const uint8_t *>(command.data());
    if(commandDecoder_feed(data, command.size()) != DECODER_COMMAND_COMPLETE)
        return;

    CommandType_t commandType;
    commandDecoder_parse(&commandType);

    switch(commandType) {
    case COMMAND_EMULATOR:
        emit emulatorStatus(SubsystemStatus::SUBSYSTEM_CONNECTED);
        break;
    case COMMAND_CONTROL:
        emit steeringStatus(SubsystemStatus::SUBSYSTEM_CONNECTED);
        break;
    case COMMAND_TELEMETRY:
        emit telemetryStatus(SubsystemStatus::SUBSYSTEM_CONNECTED);
        break;
    default:
        break;
    }
}

void CommandsManager::commandSessionClosed(const QString&)
{
    emit geolocationStatus(SubsystemStatus::SUBSYSTEM_ENABLED);
    emit telemetryStatus(SubsystemStatus::SUBSYSTEM_ENABLED);
    emit fpvStatus(SubsystemStatus::SUBSYSTEM_ENABLED);
    emit steeringStatus(SubsystemStatus::SUBSYSTEM_ENABLED);
    emit emulatorStatus(SubsystemStatus::SUBSYSTEM_ENABLED);
}
