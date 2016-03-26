////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       19.03.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "SerialPortServer.h"

#include <QSerialPortInfo>

SerialPortServer::SerialPortServer()
{
    init();
}

bool SerialPortServer::start(ServerOptions options)
{
    m_options = options.serialServer;

    m_serialPort.setPort(QSerialPortInfo(m_options.portName));
    m_serialPort.setBaudRate(m_options.baudRate);
    m_serialPort.setDataBits(m_options.dataBits);
    m_serialPort.setStopBits(m_options.stopBits);
    m_serialPort.setParity(m_options.partity);
    m_serialPort.setFlowControl(m_options.flowControl);

    m_firstIncomingData = true;
    return m_serialPort.open(QIODevice::ReadWrite);
}

void SerialPortServer::stop()
{
    if(m_serialPort.isOpen())
        m_serialPort.close();
}

bool SerialPortServer::receiveDataPriv()
{
    if(m_firstIncomingData) {
        if(m_onClientConnectedCallback)
            m_onClientConnectedCallback(getClientName());

        m_firstIncomingData = false;
    }

    m_data = m_serialPort.readAll();
    return (m_data.size() > 0);
}

void SerialPortServer::init()
{
    connect(&m_serialPort, SIGNAL(readyRead()), this, SLOT(receiveData()));
}

QString SerialPortServer::getClientName()
{
    return m_serialPort.portName();
}
