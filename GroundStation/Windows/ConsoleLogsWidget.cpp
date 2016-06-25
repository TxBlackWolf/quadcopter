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
    try {
        setOperating(false);
    }
    catch(...) {}

    delete m_ui;
}

void ConsoleLogsWidget::setOperating(bool activate)
{
    if (!activate && m_server) {
        m_server->stop();
        m_server.release();
        endLogSession();
        emit logsStatus(SubsystemStatus::SUBSYSTEM_DISABLED);
        return;
    }

    LogsOptions options;
    options.load();
    m_server.reset(IServer::create(options.serverOptions.serverType));
    m_server->setOnClientConnectedCallback(std::bind(&ConsoleLogsWidget::startLogSession, this, _1));
    m_server->setOnMessageCallback(std::bind(&ConsoleLogsWidget::appendLogs, this, _1));
    m_server->setOnClientDisconnectedCallback(std::bind(&ConsoleLogsWidget::endLogSession, this, _1));

    if (!m_server->start(options.serverOptions)) {
        QMessageBox::critical(this, "Error", "Couldn't start logs server!");
        return;
    }

    emit logsStatus(SubsystemStatus::SUBSYSTEM_ENABLED);
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

    emit logsStatus(SubsystemStatus::SUBSYSTEM_CONNECTED);
}

void ConsoleLogsWidget::appendLogs(const QByteArray& data)
{
    QMutexLocker locker(&m_mutex);

    QString message = data;
    QString currentTimestamp = QDateTime::currentDateTime().toString("[dd.MM.yyyy HH:mm] ");

    do {
        if (m_messageBuffer.isEmpty())
            m_messageBuffer = currentTimestamp;

        int n = message.indexOf("\n");
        m_messageBuffer += message.left(n);
        if (n == -1)
            break;

        m_messageBuffer += "\n";
        m_ui->textEditLogs->moveCursor(QTextCursor::End);
        m_ui->textEditLogs->insertPlainText(m_messageBuffer);
        m_logStream << m_messageBuffer;
        m_logStream.flush();

        m_messageBuffer.clear();
        message = message.right(message.size() - n - 1);
    }
    while (true);

    m_ui->textEditLogs->ensureCursorVisible();
}

void ConsoleLogsWidget::endLogSession(const QString&)
{
    if (m_logFile.isOpen())
        m_logFile.close();

    emit logsStatus(SubsystemStatus::SUBSYSTEM_ENABLED);
}
