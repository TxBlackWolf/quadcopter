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
#include "Tools/Options/CommandsOptions.h"

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
    //m_server->setOnClientConnectedCallback(std::bind(&ConsoleLogsWidget::startLogSession, this, _1));
    //m_server->setOnMessageCallback(std::bind(&ConsoleLogsWidget::appendLogs, this, _1));
    //m_server->setOnClientDisconnectedCallback(std::bind(&ConsoleLogsWidget::endLogSession, this, _1));

    m_server->start(options.serverOptions);
}

void CommandsManager::init()
{
}
