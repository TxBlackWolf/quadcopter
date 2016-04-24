////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       09.04.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef COMMANDSMANAGER_H
#define COMMANDSMANAGER_H

#include "Tools/IServer.h"

#include <QByteArray>
#include <QObject>

#include <memory>

class CommandsManager : public QObject {
    Q_OBJECT

public:
    CommandsManager();
    virtual ~CommandsManager();

public slots:
    void setOperating(bool activate);

private:
    void init();
    void parseCommand(const QByteArray& command);

private:
    std::unique_ptr<IServer> m_server;
    QByteArray m_buffer;
};

#endif
