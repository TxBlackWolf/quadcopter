////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       28.11.2014
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Misc/AboutDialog.h"

#include <QActionGroup>
#include <QMessageBox>
#include <QPixmap>

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
    delete m_googleMapsView;
    delete m_telemetryDockWidget;
    delete m_telemetryTabWidget;
    delete m_fpvDockWidget;
    delete m_systemInfoDockWidget;
    delete m_systemInfoWidget;
    delete m_alertsDockWidget;
    delete m_steeringDockWidget;
    delete m_cocpitConsoleWidget;
    delete m_emulatorDockWidget;
    delete m_emulatorWidget;
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

void MainWindow::toolbarSteeringClicked()
{
    setCentralView(CENTRAL_VIEW_STEERING);
}

void MainWindow::toolbarEmulatorClicked()
{
    setCentralView(CENTRAL_VIEW_EMULATOR);
}

void MainWindow::logsStatus(SubsystemStatus_t status)
{
    QString imageResource;
    switch(status) {
    case SUBSYSTEM_DISABLED:    imageResource = ":/Icons/Icons/led-off.png"; break;
    case SUBSYSTEM_ENABLED:     imageResource = ":/Icons/Icons/led-red.png"; break;
    case SUBSYSTEM_CONNECTED:   imageResource = ":/Icons/Icons/led-green.png"; break;
    }

    m_ui->labelLogsLED->setPixmap(QPixmap(imageResource));
}

void MainWindow::geolocationStatus(SubsystemStatus_t status)
{
    QString imageResource;
    switch(status) {
    case SUBSYSTEM_DISABLED:    imageResource = ":/Icons/Icons/led-off.png"; break;
    case SUBSYSTEM_ENABLED:     imageResource = ":/Icons/Icons/led-red.png"; break;
    case SUBSYSTEM_CONNECTED:   imageResource = ":/Icons/Icons/led-green.png"; break;
    }

    m_ui->labelGeolocationLED->setPixmap(QPixmap(imageResource));
}

void MainWindow::telemetryStatus(SubsystemStatus_t status)
{
    QString imageResource;
    switch(status) {
    case SUBSYSTEM_DISABLED:    imageResource = ":/Icons/Icons/led-off.png"; break;
    case SUBSYSTEM_ENABLED:     imageResource = ":/Icons/Icons/led-red.png"; break;
    case SUBSYSTEM_CONNECTED:   imageResource = ":/Icons/Icons/led-green.png"; break;
    }

    m_ui->labelTelemetryLED->setPixmap(QPixmap(imageResource));
}

void MainWindow::fpvStatus(SubsystemStatus_t status)
{
    QString imageResource;
    switch(status) {
    case SUBSYSTEM_DISABLED:    imageResource = ":/Icons/Icons/led-off.png"; break;
    case SUBSYSTEM_ENABLED:     imageResource = ":/Icons/Icons/led-red.png"; break;
    case SUBSYSTEM_CONNECTED:   imageResource = ":/Icons/Icons/led-green.png"; break;
    }

    m_ui->labelFPVLED->setPixmap(QPixmap(imageResource));
}

void MainWindow::steeringStatus(SubsystemStatus_t status)
{
    QString imageResource;
    switch(status) {
    case SUBSYSTEM_DISABLED:    imageResource = ":/Icons/Icons/led-off.png"; break;
    case SUBSYSTEM_ENABLED:     imageResource = ":/Icons/Icons/led-red.png"; break;
    case SUBSYSTEM_CONNECTED:   imageResource = ":/Icons/Icons/led-green.png"; break;
    }

    m_ui->labelSteeringLED->setPixmap(QPixmap(imageResource));
}

void MainWindow::emulatorStatus(SubsystemStatus_t status)
{
    QString imageResource;
    switch(status) {
    case SUBSYSTEM_DISABLED:    imageResource = ":/Icons/Icons/led-off.png"; break;
    case SUBSYSTEM_ENABLED:     imageResource = ":/Icons/Icons/led-red.png"; break;
    case SUBSYSTEM_CONNECTED:   imageResource = ":/Icons/Icons/led-green.png"; break;
    }

    m_ui->labelEmulatorLED->setPixmap(QPixmap(imageResource));
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
    m_actionGroup->addAction(m_ui->toolbarSteering);
    m_actionGroup->addAction(m_ui->toolbarEmulator);

    initTopDockWidgets();
    initCentralWidgets();
    m_ui->connectionDockWidget->setTitleBarWidget(new QWidget());

    connect(m_ui->toolbarLogs, SIGNAL(triggered()), this, SLOT(toolbarLogsClicked()));
    connect(m_ui->toolbarGeolocation, SIGNAL(triggered()), this, SLOT(toolbarGeolocationClicked()));
    connect(m_ui->toolbarTelemetry, SIGNAL(triggered()), this, SLOT(toolbarTelemetryClicked()));
    connect(m_ui->toolbarFPV, SIGNAL(triggered()), this, SLOT(toolbarFPVClicked()));
    connect(m_ui->toolbarSystemInfo, SIGNAL(triggered()), this, SLOT(toolbarSystemInfoClicked()));
    connect(m_ui->toolbarAlerts, SIGNAL(triggered()), this, SLOT(toolbarAlertsClicked()));
    connect(m_ui->toolbarSteering, SIGNAL(triggered()), this, SLOT(toolbarSteeringClicked()));
    connect(m_ui->toolbarEmulator, SIGNAL(triggered()), this, SLOT(toolbarEmulatorClicked()));
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

    m_steeringDockWidget = new SteeringDockWidget();
    m_steeringDockWidget->hide();
    addDockWidget(Qt::TopDockWidgetArea, m_steeringDockWidget);

    m_emulatorDockWidget = new EmulatorDockWidget();
    m_emulatorDockWidget->hide();
    addDockWidget(Qt::TopDockWidgetArea, m_emulatorDockWidget);

    setDockNestingEnabled(true);
}

void MainWindow::initCentralWidgets()
{
    m_consoleLogsWidget = new ConsoleLogsWidget();
    m_googleMapsView = new GoogleMapsView();
    m_telemetryTabWidget = new TelemetryTabWidget();
    m_systemInfoWidget = new SystemInfoWidget();
    m_cocpitConsoleWidget = new CocpitConsoleWidget();
    m_emulatorWidget = new EmulatorWidget();

    connect(m_consoleLogsWidget, SIGNAL(logsStatus(SubsystemStatus_t)), this, SLOT(logsStatus(SubsystemStatus_t)));
    connect(m_emulatorWidget, SIGNAL(emulatorStatus(SubsystemStatus_t)), this, SLOT(emulatorStatus(SubsystemStatus_t)));

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
        setCentralWidget(m_googleMapsView);
        break;
	case CENTRAL_VIEW_TELEMETRY:
        m_currentTopDockWidget = m_telemetryDockWidget;
        setCentralWidget(m_telemetryTabWidget);
        break;
    case CENTRAL_VIEW_FPV:
        m_currentTopDockWidget = m_fpvDockWidget;
        break;
    case CENTRAL_VIEW_SYSTEM_INFO:
        m_currentTopDockWidget = m_systemInfoDockWidget;
        setCentralWidget(m_systemInfoWidget);
        break;
    case CENTRAL_VIEW_ALERTS:
        m_currentTopDockWidget = m_alertsDockWidget;
        break;
    case CENTRAL_VIEW_STEERING:
        m_currentTopDockWidget = m_steeringDockWidget;
        setCentralWidget(m_cocpitConsoleWidget);
        break;
    case CENTRAL_VIEW_EMULATOR:
        m_currentTopDockWidget = m_emulatorDockWidget;
        setCentralWidget(m_emulatorWidget);
        break;
    default:
        break;
    }

    m_currentTopDockWidget->show();
}
