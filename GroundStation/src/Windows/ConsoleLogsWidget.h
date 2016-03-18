////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       14.01.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CONSOLELOGSWIDGET_H
#define CONSOLELOGSWIDGET_H

#include "Misc/SubsystemsStatus.h"
#include "Tools/IServer.h"

#include <QFile>
#include <QMutex>
#include <QTextStream>
#include <QWidget>

#include <memory>

namespace Ui {
	class ConsoleLogsWidget;
}

class ConsoleLogsWidget : public QWidget {
	Q_OBJECT

public:
	explicit ConsoleLogsWidget(QWidget* parent = nullptr);
	virtual ~ConsoleLogsWidget();

signals:
	void logsStatus(SubsystemStatus_t);

public slots:
    void setOperating(bool activate);

private:
	void init();
    void startLogSession(const QString&);
    void appendLogs(const QByteArray& data);
    void endLogSession(const QString&);

private:
	Ui::ConsoleLogsWidget* m_ui;

	QMutex m_mutex;
	QFile m_logFile;
	QTextStream m_logStream;

	std::unique_ptr<IServer> m_server;
};

#endif
