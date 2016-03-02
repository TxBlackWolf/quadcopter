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

#include <QByteArray>
#include <QObject>

#include <functional>
#include <memory>

class IServer : public QObject {
    Q_OBJECT

public:
    static std::unique_ptr<IServer> create();

    virtual bool start() = 0;
    virtual void stop() = 0;
    void setMessageCallback(std::function<void(const QByteArray&)> onMessageCallback);

public slots:
    void receiveData();

protected:
    IServer() {}
    virtual bool receiveSpecificData() = 0;

protected:
    QByteArray m_data;

private:
    std::function<void(const QByteArray&)> m_onMessageCallback;
};

#endif
