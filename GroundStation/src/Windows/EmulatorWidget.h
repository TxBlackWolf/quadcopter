////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       08.02.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef EMULATORWIDGET_H
#define EMULATORWIDGET_H

#include "Misc/SubsystemsStatus.h"

#include <QTcpServer>
#include <QTcpSocket>
#include <QWidget>

#include <cstdint>

namespace Ui {
    class EmulatorWidget;
}

class EmulatorWidget : public QWidget {
    Q_OBJECT

public:
    explicit EmulatorWidget(QWidget* parent = nullptr);
    virtual ~EmulatorWidget();

signals:
    void emulatorStatus(SubsystemStatus);

public slots:
    void startEmulatorServer();
    void stopEmulatorServer();
    void accept();
    void readSocket();
    void clientDisconnected();

private:
    void init();
    void initCommandsFramework();
    static void gpioCallback(uint8_t* buffer, uint32_t size);

private:
    Ui::EmulatorWidget* m_ui;

    QTcpServer m_tcpServer;
    QTcpSocket* m_socket;
};

#endif
