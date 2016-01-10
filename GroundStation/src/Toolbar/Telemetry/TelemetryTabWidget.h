//============================================================================
//
// Filename   : TelemetryTabWidget.h
// Author     : Kuba Sejdak
// Created on : 23 mar 2015
//
//============================================================================

#ifndef TELEMETRYTABWIDGET_H
#define TELEMETRYTABWIDGET_H

#include "Common/TCP/TCPServer.h"
#include "Common/Telemetry/Telemetry.h"

#include <memory>
#include <vector>
#include <map>
#include <string>
#include <cstdint>
#include <mutex>

#include <QTabWidget>
#include <QTreeWidgetItem>
#include <QList>

namespace Ui
{
    class TelemetryTabWidget;
}

class TelemetryTabWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit TelemetryTabWidget(QWidget* parent = 0);
    ~TelemetryTabWidget();

private:
    void onConnected(const std::string& clientEndpoint, const boost::system::error_code& error);
    void onDisconnected(const std::string& clientEndpoint);
    void onMessage(const std::string& clientEndpoint, const std::vector<uint8_t>& message);

    void addClient(const std::string& clientName, const std::string& clientEndpoint);
    void removeClient(const std::string& clientName);
    void addObject(const std::string& clientName, ITelemetryObject* object);
    void updateObject(const std::string& clientName, ITelemetryObject* object);
    void removeObject(const std::string& clientName, const std::string& objectName);

    void clear();

    int findClientItemIndex(const std::string& clientName);
    int findObjectItemIndex(const std::string& clientName, const std::string& objectName);
    QString objectValueToString(ITelemetryObject* object) const;

private slots:
    void onClearButtonClicked();

private:
    Ui::TelemetryTabWidget* m_ui;

    std::mutex m_mutex;
    std::map<std::string, std::string> m_clientEndpointToNameMap;
    std::map<std::string, std::shared_ptr<TelemetryObjectsRegister>> m_objectsRegister;
    QList<QTreeWidgetItem*> m_treeItems;
    bool m_keepObjectsAlive;

    boost::scoped_ptr<TCPServer> m_tcpServer;
};

#endif
