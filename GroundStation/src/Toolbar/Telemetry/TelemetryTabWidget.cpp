//============================================================================
//
// Filename   : TelemetryTabWidget.cpp
// Author     : Kuba Sejdak
// Created on : 23 mar 2015
//
//============================================================================

#include "TelemetryTabWidget.h"
#include "ui_TelemetryTabWidget.h"

#include "Common/Telemetry/Telemetry.h"

#include <QMessageBox>

#include <functional>
#include <iostream>
#include <cassert>
#include <boost/range/adaptors.hpp>

static const int TELEMETRY_SERVER_LISTEN_PORT = 12345;
static const int COLUMN_CLIENT_NAME           = 0;
static const int COLUMN_CLIENT_ADDRESS        = 1;
static const int COLUMN_THREAD_NAME           = 2;
static const int COLUMN_OBJECT_NAME           = 3;
static const int COLUMN_OBJECT_TYPE           = 4;
static const int COLUMN_OBJECT_VALUE          = 5;

TelemetryTabWidget::TelemetryTabWidget(QWidget* parent)
    : QTabWidget(parent)
    , m_ui(new Ui::TelemetryTabWidget)
    , m_keepObjectsAlive(true)
    , m_tcpServer(new TCPServer(TELEMETRY_SERVER_LISTEN_PORT,
                                std::bind(&TelemetryTabWidget::onConnected, this, std::placeholders::_1, std::placeholders::_2),
                                std::bind(&TelemetryTabWidget::onDisconnected, this, std::placeholders::_1),
                                std::bind(&TelemetryTabWidget::onMessage, this, std::placeholders::_1, std::placeholders::_2)))
{
    m_ui->setupUi(this);
    m_tcpServer->start();

    // This is just to keep Qt warnings quiet.
    qRegisterMetaType<QVector<int>>("QVector<int>");

    connect(m_ui->buttonClear, SIGNAL(clicked()), this, SLOT(onClearButtonClicked()));
}

TelemetryTabWidget::~TelemetryTabWidget()
{
    clear();
    delete m_ui;
}

void TelemetryTabWidget::onConnected(const std::string& clientEndpoint, const boost::system::error_code& error)
{
    if(error)
    {
        std::cout << "Error when connecting to client: " << clientEndpoint << "." << std::endl;
        std::cout << "Cause: " << error.message() << "." << std::endl;
        return;
    }
}

void TelemetryTabWidget::onDisconnected(const std::string& clientEndpoint)
{
    std::unique_lock<std::mutex> lock(m_mutex);

    if(m_keepObjectsAlive)
        return;

    std::string clientName = m_clientEndpointToNameMap[clientEndpoint];
    m_objectsRegister.erase(clientName);

    removeClient(clientName);
}

void TelemetryTabWidget::onMessage(const std::string& clientEndpoint, const std::vector<uint8_t>& message)
{
    TelemetryMessage telemetryMessage;
    telemetryMessage.deserialize(const_cast<std::vector<uint8_t>&>(message));

    TelemetryMessageType messageType = telemetryMessage.getMessageType();
    if(messageType == MESSAGE_TYPE_HELLO)
    {
        std::unique_lock<std::mutex> lock(m_mutex);

        std::string clientName = telemetryMessage.getClientName();
        m_clientEndpointToNameMap[clientEndpoint] = clientName;

        // Check if client is a duplicate.
        if(m_objectsRegister.find(clientName) != m_objectsRegister.end())
        {
            // This client is already known, because of 'keep alive" option.
            if(m_keepObjectsAlive)
                return;

            // Two different clients (or instances) with the same name.
            QMessageBox::warning(this,
                                 "Client error.",
                                 "This client name is already known. Choose another name.",
                                 QMessageBox::Ok);
            return;
        }

        std::shared_ptr<TelemetryObjectsRegister> clientObjects(new TelemetryObjectsRegister());
        m_objectsRegister[clientName] = clientObjects;

        addClient(clientName, clientEndpoint);
    }
    else if(messageType == MESSAGE_TYPE_REGISTER_OBJECT)
    {
        std::unique_lock<std::mutex> lock(m_mutex);

        std::string clientName = m_clientEndpointToNameMap[clientEndpoint];
        TelemetryObjectType objectType = telemetryMessage.getObjectType();
        std::string objectName = telemetryMessage.getObjectName();

        // Check if object is a duplicate.
        if(m_objectsRegister[clientName]->getObject(objectType, objectName) != nullptr)
        {
            // This object is already known, because of 'keep alive" option.
            if(m_keepObjectsAlive)
                return;

            // Two different clients (or instances) with the same name.
            QMessageBox::warning(this,
                                 "Client error.",
                                 "This object name is already known. Choose another name.",
                                 QMessageBox::Ok);
            return;
        }

        ITelemetryObject* object = TelemetryObjectAccessor::create(objectName,
                                                                   objectType,
                                                                   telemetryMessage.getObjectInternalType());
        object->deserialize(telemetryMessage.getMessageData());
        m_objectsRegister[clientName]->addObject(object);

        addObject(clientName, object);
    }
    else if(messageType == MESSAGE_TYPE_UNREGISTER_OBJECT)
    {
        std::unique_lock<std::mutex> lock(m_mutex);

        if(m_keepObjectsAlive)
            return;

        std::string clientName = m_clientEndpointToNameMap[clientEndpoint];
        TelemetryObjectType objectType = telemetryMessage.getObjectType();
        std::string objectName = telemetryMessage.getObjectName();
        ITelemetryObject* object = m_objectsRegister[clientName]->getObject(objectType, objectName);
        delete object;
        m_objectsRegister[clientName]->removeObject(objectType, objectName);

        removeObject(clientName, objectName);
    }
    else if(messageType == MESSAGE_TYPE_DISABLE_OBJECT)
    {
        // TODO: implement.
    }
    else if(messageType == MESSAGE_TYPE_ENABLE_OBJECT)
    {
        // TODO: implement.
    }
    else if(messageType == MESSAGE_TYPE_SET_VALUE)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        std::string clientName = m_clientEndpointToNameMap[clientEndpoint];
        ITelemetryObject* object = m_objectsRegister[clientName]->getObject(telemetryMessage.getObjectType(), telemetryMessage.getObjectName());
        object->deserialize(telemetryMessage.getMessageData());

        updateObject(clientEndpoint, object);
    }
    else if(messageType == MESSAGE_TYPE_GET_VALUE)
    {
        // TODO: implement.
    }
    else if(messageType == MESSAGE_TYPE_FREEZE_THREAD)
    {
        // TODO: implement.
    }
    else if(messageType == MESSAGE_TYPE_THAW_THREAD)
    {
        // TODO: implement.
    }
}

void TelemetryTabWidget::addClient(const std::string& clientName, const std::string& clientEndpoint)
{
    QTreeWidgetItem* clientItem = new QTreeWidgetItem();
    clientItem->setText(COLUMN_CLIENT_NAME, clientName.c_str());
    clientItem->setText(COLUMN_CLIENT_ADDRESS, clientEndpoint.c_str());
    clientItem->setChildIndicatorPolicy(QTreeWidgetItem::DontShowIndicatorWhenChildless);

    m_ui->treeWidget->addTopLevelItem(clientItem);
    m_treeItems.push_back(clientItem);
}

void TelemetryTabWidget::removeClient(const std::string& clientName)
{
    int clientIndex = findClientItemIndex(clientName);
    m_ui->treeWidget->topLevelItem(clientIndex)->takeChildren();
    m_ui->treeWidget->takeTopLevelItem(clientIndex);
}

void TelemetryTabWidget::addObject(const std::string& clientName, ITelemetryObject* object)
{
    QTreeWidgetItem* objectItem = new QTreeWidgetItem();
    objectItem->setText(COLUMN_THREAD_NAME, object->getThreadName().c_str());
    objectItem->setText(COLUMN_OBJECT_NAME, object->getName().c_str());
    objectItem->setText(COLUMN_OBJECT_TYPE, object->getInternalTypeName().c_str());
    objectItem->setText(COLUMN_OBJECT_VALUE, objectValueToString(object));

    int clientIndex = findClientItemIndex(clientName);
    QTreeWidgetItem* clientItem = m_ui->treeWidget->topLevelItem(clientIndex);
    clientItem->addChild(objectItem);
    clientItem->setExpanded(true);
    m_treeItems.push_back(objectItem);
}

void TelemetryTabWidget::updateObject(const std::string& clientName, ITelemetryObject* object)
{
    int clientIndex = findClientItemIndex(clientName);
    QTreeWidgetItem* clientItem = m_ui->treeWidget->topLevelItem(clientIndex);
    int objectIndex = findObjectItemIndex(clientName, object->getName());
    QTreeWidgetItem* objectItem = clientItem->child(objectIndex);
    objectItem->setText(COLUMN_OBJECT_VALUE, objectValueToString(object));
}

void TelemetryTabWidget::removeObject(const std::string& clientName, const std::string& objectName)
{
    int clientIndex = findClientItemIndex(clientName);
    QTreeWidgetItem* clientItem = m_ui->treeWidget->topLevelItem(clientIndex);

    int objectIndex = findObjectItemIndex(clientName, objectName);
    clientItem->removeChild(clientItem->child(objectIndex));
}

void TelemetryTabWidget::clear()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    for(const std::string& clientName : m_objectsRegister | boost::adaptors::map_keys)
        removeClient(clientName);

    m_clientEndpointToNameMap.clear();
    m_objectsRegister.clear();
    qDeleteAll(m_treeItems);
    m_treeItems.clear();
}

int TelemetryTabWidget::findClientItemIndex(const std::string& clientName)
{
    int clientItemsCount = m_ui->treeWidget->topLevelItemCount();
    for(int i = 0; i < clientItemsCount; ++i)
    {
        if(m_ui->treeWidget->topLevelItem(i)->text(COLUMN_CLIENT_NAME) == clientName.c_str())
            return i;
    }

    assert(false);
}

int TelemetryTabWidget::findObjectItemIndex(const std::string& clientName, const std::string& objectName)
{
    int clientIndex = findClientItemIndex(clientName);
    QTreeWidgetItem* clientItem = m_ui->treeWidget->topLevelItem(clientIndex);

    int childObjectItemsCount = clientItem->childCount();
    for(int i = 0; i < childObjectItemsCount; ++i)
    {
        if(clientItem->child(i)->text(COLUMN_OBJECT_NAME) == objectName.c_str())
            return i;
    }

    assert(false);
}

QString TelemetryTabWidget::objectValueToString(ITelemetryObject* object) const
{
    switch(object->getInternalType())
    {
    case TelemetryTypeSupport<int>::id:                 return QString::number(object->toWatchableObject<int>()->getValue());
    case TelemetryTypeSupport<unsigned int>::id:        return QString::number(object->toWatchableObject<unsigned int>()->getValue());
    case TelemetryTypeSupport<short int>::id:           return QString::number(object->toWatchableObject<short int>()->getValue());
    case TelemetryTypeSupport<unsigned short int>::id:  return QString::number(object->toWatchableObject<unsigned short int>()->getValue());
    case TelemetryTypeSupport<long int>::id:            return QString::number(object->toWatchableObject<long int>()->getValue());
    case TelemetryTypeSupport<unsigned long int>::id:   return QString::number(object->toWatchableObject<unsigned long int>()->getValue());
    case TelemetryTypeSupport<float>::id:               return QString::number(object->toWatchableObject<float>()->getValue());
    case TelemetryTypeSupport<double>::id:              return QString::number(object->toWatchableObject<double>()->getValue());
    case TelemetryTypeSupport<long double>::id:         return QString::number(object->toWatchableObject<double>()->getValue());
    case TelemetryTypeSupport<char>::id:                return QString::number(object->toWatchableObject<char>()->getValue());
    case TelemetryTypeSupport<unsigned char>::id:       return QString::number(object->toWatchableObject<unsigned char>()->getValue());
    case TelemetryTypeSupport<bool>::id:                return object->toWatchableObject<bool>()->getValue() ? "true" : "false";
    case TelemetryTypeSupport<std::string>::id:         return object->toWatchableObject<std::string>()->getValue().c_str();
    }

    assert(false);
}

void TelemetryTabWidget::onClearButtonClicked()
{
    clear();
}
