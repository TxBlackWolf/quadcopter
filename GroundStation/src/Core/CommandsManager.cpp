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
#include "common/commands/commands.h"
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
        setOperating(false);
    }
    catch(...) {}
}

void CommandsManager::setOperating(bool activate)
{
    if(!activate && m_server) {
        m_server->stop();
        m_server.release();
        return;
    }

    CommandsOptions options;
    options.load();
    m_server.reset(IServer::create(options.serverOptions.serverType));
    m_server->setOnMessageCallback(std::bind(&CommandsManager::parseCommand, this, _1));

    m_server->start(options.serverOptions);
}

void CommandsManager::init()
{
}

void CommandsManager::parseCommand(const QByteArray& command)
{
    uint8_t* data = reinterpret_cast<uint8_t *>(const_cast<char *>(command.toStdString().data()));
    command_parse(data);
}
