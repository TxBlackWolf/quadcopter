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
    m_buffer = new uint8_t[2 * COMMAND_MAX_SIZE_BYTES];
    commandDecoder_init(m_buffer);
}

void CommandsManager::parseCommand(const QByteArray& command)
{
    const uint8_t* data = reinterpret_cast<const uint8_t *>(command.data());
    if(commandDecoder_feed(data, command.size()) != DECODER_COMMAND_COMPLETE)
        return;

    commandDecoder_parse();
}
