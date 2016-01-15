//=============================================================================================
//
// Filename   : MainWindow.cpp
// Author     : Kuba Sejdak
// Created on : 28.11.2014
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//=============================================================================================

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Misc/AboutDialog.h"

#include <QActionGroup>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow())
    , m_currentTopDockWidget(nullptr)
{
    m_ui->setupUi(this);

    init();
    showMaximized();
}

MainWindow::~MainWindow()
{
    if(centralWidget()) {
        // This prevents QMainWindow from deleting central widget (because it takes ownership of it).
        centralWidget()->setParent(nullptr);
    }

    delete m_ui;
    delete m_actionGroup;
    delete m_logsDockWidget;
    delete m_consoleLogsWidget;
    delete m_geolocationDockWidget;
    delete m_telemetryDockWidget;
    delete m_fpvDockWidget;
    delete m_systemInfoDockWidget;
    delete m_alertsDockWidget;
}

void MainWindow::toolbarLogsClicked()
{
    setCentralView(CENTRAL_VIEW_LOGS);
}

void MainWindow::toolbarGeolocationClicked()
{
    setCentralView(CENTRAL_VIEW_GEOLOCATION);
}

void MainWindow::toolbarTelemetryClicked()
{
    setCentralView(CENTRAL_VIEW_TELEMETRY);
}

void MainWindow::toolbarFPVClicked()
{
    setCentralView(CENTRAL_VIEW_FPV);
}

void MainWindow::toolbarSystemInfoClicked()
{
    setCentralView(CENTRAL_VIEW_SYSTEM_INFO);
}

void MainWindow::toolbarAlertsClicked()
{
    setCentralView(CENTRAL_VIEW_ALERTS);
}

void MainWindow::init()
{
    m_actionGroup = new QActionGroup(this);
    m_actionGroup->setExclusive(true);
    m_actionGroup->addAction(m_ui->toolbarLogs);
    m_actionGroup->addAction(m_ui->toolbarGeolocation);
    m_actionGroup->addAction(m_ui->toolbarTelemetry);
    m_actionGroup->addAction(m_ui->toolbarFPV);
    m_actionGroup->addAction(m_ui->toolbarSystemInfo);
    m_actionGroup->addAction(m_ui->toolbarAlerts);

    initTopDockWidgets();
    initCentralWidgets();

    connect(m_ui->toolbarLogs, SIGNAL(triggered()), this, SLOT(toolbarLogsClicked()));
    connect(m_ui->toolbarGeolocation, SIGNAL(triggered()), this, SLOT(toolbarGeolocationClicked()));
    connect(m_ui->toolbarTelemetry, SIGNAL(triggered()), this, SLOT(toolbarTelemetryClicked()));
    connect(m_ui->toolbarFPV, SIGNAL(triggered()), this, SLOT(toolbarFPVClicked()));
    connect(m_ui->toolbarSystemInfo, SIGNAL(triggered()), this, SLOT(toolbarSystemInfoClicked()));
    connect(m_ui->toolbarAlerts, SIGNAL(triggered()), this, SLOT(toolbarAlertsClicked()));
}

void MainWindow::initTopDockWidgets()
{
    m_logsDockWidget = new LogsDockWidget();
    m_logsDockWidget->hide();
    addDockWidget(Qt::TopDockWidgetArea, m_logsDockWidget);

    m_geolocationDockWidget = new GeolocationDockWidget();
    m_geolocationDockWidget->hide();
    addDockWidget(Qt::TopDockWidgetArea, m_geolocationDockWidget);

    m_telemetryDockWidget = new TelemetryDockWidget();
    m_telemetryDockWidget->hide();
    addDockWidget(Qt::TopDockWidgetArea, m_telemetryDockWidget);

    m_fpvDockWidget = new FPVDockWidget();
    m_fpvDockWidget->hide();
    addDockWidget(Qt::TopDockWidgetArea, m_fpvDockWidget);

    m_systemInfoDockWidget = new SystemInfoDockWidget();
    m_systemInfoDockWidget->hide();
    addDockWidget(Qt::TopDockWidgetArea, m_systemInfoDockWidget);

    m_alertsDockWidget = new AlertsDockWidget();
    m_alertsDockWidget->hide();
    addDockWidget(Qt::TopDockWidgetArea, m_alertsDockWidget);

    setDockNestingEnabled(true);
}

void MainWindow::initCentralWidgets()
{
    m_consoleLogsWidget = new ConsoleLogsWidget();

    setCentralView(CENTRAL_VIEW_LOGS);
    m_ui->toolbarLogs->setChecked(true);
}

void MainWindow::setCentralView(CentralView centralView)
{
    if(m_currentTopDockWidget)
        m_currentTopDockWidget->hide();

    if(centralWidget()) {
        // This prevents QMainWindow from deleting central widget (because it takes ownership of it).
        centralWidget()->setParent(nullptr);
    }

    switch(centralView) {
    case CENTRAL_VIEW_LOGS:
        m_currentTopDockWidget = m_logsDockWidget;
        setCentralWidget(m_consoleLogsWidget);
        break;
    case CENTRAL_VIEW_GEOLOCATION:
        m_currentTopDockWidget = m_geolocationDockWidget;
        break;
	case CENTRAL_VIEW_TELEMETRY:
		m_currentTopDockWidget = m_telemetryDockWidget;
		break;
    case CENTRAL_VIEW_FPV:
        m_currentTopDockWidget = m_fpvDockWidget;
        break;
    case CENTRAL_VIEW_SYSTEM_INFO:
        m_currentTopDockWidget = m_systemInfoDockWidget;
        break;
    case CENTRAL_VIEW_ALERTS:
        m_currentTopDockWidget = m_alertsDockWidget;
        break;
    default:
        break;
    }

    m_currentTopDockWidget->show();
}
