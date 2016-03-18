////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       26.02.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef ISERVER_H
#define ISERVER_H

#include "Options/ServerOptions.h"

#include <QByteArray>
#include <QObject>

#include <functional>

class IServer : public QObject {
	Q_OBJECT

public:
    static IServer* create(ServerOptions::ServerType type);

	virtual bool start(ServerOptions options) = 0;
	virtual void stop() = 0;
	void setOnClientConnectedCallback(std::function<void(const QString&)> onClientConnectedCallback);
	void setOnMessageCallback(std::function<void(const QByteArray&)> onMessageCallback);
	void setOnClientDisconnectedCallback(std::function<void(const QString&)> onClientDisconnectedCallback);

public slots:
    virtual void acceptConnection() = 0;
	void receiveData();
    virtual void clientDisconnected() = 0;

protected:
	IServer() {}
    virtual bool receiveDataPriv() = 0;

protected:
	QByteArray m_data;
	std::function<void(const QString&)> m_onClientConnectedCallback;
	std::function<void(const QByteArray&)> m_onMessageCallback;
	std::function<void(const QString&)> m_onClientDisconnectedCallback;
};

#endif
