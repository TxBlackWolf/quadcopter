////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       14.01.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "ConsoleLogsWidget.h"
#include "ui_ConsoleLogsWidget.h"

#include "Tools/Options/LogsOptions.h"

#include <QDateTime>
#include <QDir>
#include <QMessageBox>
#include <QMutexLocker>

using namespace std::placeholders;

ConsoleLogsWidget::ConsoleLogsWidget(QWidget* parent)
    : QWidget(parent)
    , m_ui(new Ui::ConsoleLogsWidget())
    , m_logStream(&m_logFile)
{
    m_ui->setupUi(this);
    init();
}

ConsoleLogsWidget::~ConsoleLogsWidget()
{
	delete m_ui;
}

void ConsoleLogsWidget::setOperating(bool activate)
{
    if(!activate) {
        m_server->stop();
        m_server.release();
        //m_logFile.close();
        emit logsStatus(SubsystemStatus_t::SUBSYSTEM_DISABLED);
        return;
    }

    LogsOptions options;
    options.load();
    m_server.reset(IServer::create(options.serverOptions.serverType));
    m_server->setOnClientConnectedCallback(std::bind(&ConsoleLogsWidget::startLogSession, this, _1));
    m_server->setOnMessageCallback(std::bind(&ConsoleLogsWidget::appendLogs, this, _1));
    m_server->setOnClientDisconnectedCallback(std::bind(&ConsoleLogsWidget::endLogSession, this, _1));

    if(!m_server->start(options.serverOptions)) {
        QMessageBox::critical(this, "Error", "Couldn't start logs server!");
        return;
    }

    emit logsStatus(SubsystemStatus_t::SUBSYSTEM_ENABLED);
}

void ConsoleLogsWidget::init()
{
	connect(m_ui->buttonClear, SIGNAL(clicked()), m_ui->textEditLogs, SLOT(clear()));
}

void ConsoleLogsWidget::startLogSession(const QString&)
{
    LogsOptions options;
    options.load();

    QDir().mkpath(options.logsPath);
    QString logFileName = QString("%1/GroundStation_%2.log").arg(options.logsPath).arg(QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss"));
    m_logFile.setFileName(logFileName);
    m_logFile.open(QFile::Append | QFile::Text);

    emit logsStatus(SubsystemStatus_t::SUBSYSTEM_CONNECTED);
}

void ConsoleLogsWidget::appendLogs(const QByteArray& data)
{
    QString message = data;
    QString currentTimestamp = QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm");
    message = "[" + currentTimestamp + "] " + message;

    QMutexLocker locker(&m_mutex);
    m_ui->textEditLogs->insertPlainText(message);
    m_logStream << message;
    m_logStream.flush();
}

void ConsoleLogsWidget::endLogSession(const QString&)
{
    m_logFile.close();
    emit logsStatus(SubsystemStatus_t::SUBSYSTEM_ENABLED);
}
