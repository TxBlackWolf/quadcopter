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

#include "Misc/SubsystemsStatus.h"
#include "Tools/IServer.h"

#include <QObject>

#include <memory>
#include <cstdint>

class CommandsManager : public QObject {
    Q_OBJECT

public:
    typedef enum {

    } SteeringEvents;

    CommandsManager();
    virtual ~CommandsManager();

signals:
    void geolocationStatus(SubsystemStatus);
    void telemetryStatus(SubsystemStatus);
    void fpvStatus(SubsystemStatus);
    void steeringStatus(SubsystemStatus);
    void emulatorStatus(SubsystemStatus);

public slots:
    void setOperating(bool activate);

private:
    void init();
    void parseCommand(const QByteArray& command);
    void commandSessionClosed(const QString&);

private:
    std::unique_ptr<IServer> m_server;
    uint8_t* m_buffer;
};

#endif
