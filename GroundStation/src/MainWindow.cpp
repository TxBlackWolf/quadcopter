//============================================================================
//
// Filename   : MainWindow.cpp
// Author     : Kuba Sejdak
// Created on : 28 lis 2014
//
//============================================================================

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Misc/AboutDialog.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
    , m_centralView(CENTRAL_VIEW_UNKNOWN)
    , m_currentlySelectedToolbar(nullptr)
    , m_currentTopDockWidget(nullptr)
{
    m_ui->setupUi(this);

    init();
    showMaximized();
}

MainWindow::~MainWindow()
{
    if(centralWidget())
    {
        // This to prevent QMainWindow from deleting central widget (because it takes ownership of it).
        centralWidget()->setParent(nullptr);
    }

    delete m_ui;
    delete m_logsDockWidget;
    delete m_consoleLogsWidget;
    delete m_geolocationDockWidget;
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

void MainWindow::setCentralView(CentralView centralView)
{
    if(m_centralView == centralView)
    {
        // Clicked icon is already clicked, then do nothing.
        m_currentlySelectedToolbar->setChecked(true);
        return;
    }

    if(m_currentlySelectedToolbar)
        m_currentlySelectedToolbar->setChecked(false);

    if(m_currentTopDockWidget)
        m_currentTopDockWidget->hide();

    if(centralWidget())
    {
        // This to prevent QMainWindow from deleting central widget (because it takes ownership of it).
        centralWidget()->setParent(nullptr);
    }

    switch(centralView)
    {
    case CENTRAL_VIEW_LOGS:
        m_currentlySelectedToolbar = m_ui->toolbarLogs;
        m_currentTopDockWidget = m_logsDockWidget;
        setCentralWidget(m_consoleLogsWidget);
        break;
    case CENTRAL_VIEW_GEOLOCATION:
        m_currentlySelectedToolbar = m_ui->toolbarGeolocation;
        m_currentTopDockWidget = m_geolocationDockWidget;
        break;
    case CENTRAL_VIEW_FPV:
        m_currentlySelectedToolbar = m_ui->toolbarFPV;
        m_currentTopDockWidget = m_fpvDockWidget;
        break;
    case CENTRAL_VIEW_SYSTEM_INFO:
        m_currentlySelectedToolbar = m_ui->toolbarSystemInfo;
        m_currentTopDockWidget = m_systemInfoDockWidget;
        break;
    case CENTRAL_VIEW_ALERTS:
        m_currentlySelectedToolbar = m_ui->toolbarAlerts;
        m_currentTopDockWidget = m_alertsDockWidget;
        break;
    default:
        break;
    }

    m_currentlySelectedToolbar->setChecked(true);
    m_currentTopDockWidget->show();
}

void MainWindow::init()
{
    initTopDockWidgets();
    initCentralWidgets();

    connect(m_ui->toolbarLogs, SIGNAL(triggered()), this, SLOT(toolbarLogsClicked()));
    connect(m_ui->toolbarGeolocation, SIGNAL(triggered()), this, SLOT(toolbarGeolocationClicked()));
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
}
