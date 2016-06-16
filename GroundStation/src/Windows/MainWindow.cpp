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

#include "AboutDialog.h"

#include <QActionGroup>
#include <QMessageBox>
#include <QPixmap>

#include <memory>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow())
    , m_steeringController(m_commandsManager)
{
    m_ui->setupUi(this);

    init();
}

MainWindow::~MainWindow()
{
    try {
        if (centralWidget()) {
            // This prevents QMainWindow from deleting central widget (because it takes ownership of it).
            centralWidget()->setParent(nullptr);
        }
    }
    catch(...) {}

    delete m_ui;
    delete m_actionGroup;
    delete m_settingsWidget;
    delete m_consoleLogsWidget;
    delete m_googleMapsView;
    delete m_telemetryTabWidget;
    delete m_fpvView;
    delete m_systemInfoWidget;
    delete m_alertsWidget;
    delete m_cocpitConsoleWidget;
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

void MainWindow::logsStatus(SubsystemStatus status)
{
    QString imageResource = getSubsystemStatusImage(status);
    m_ui->labelLogsLED->setPixmap(QPixmap(imageResource));
}

void MainWindow::geolocationStatus(SubsystemStatus status)
{
    QString imageResource = getSubsystemStatusImage(status);
    m_ui->labelGeolocationLED->setPixmap(QPixmap(imageResource));
}

void MainWindow::telemetryStatus(SubsystemStatus status)
{
    QString imageResource = getSubsystemStatusImage(status);
    m_ui->labelTelemetryLED->setPixmap(QPixmap(imageResource));
}

void MainWindow::fpvStatus(SubsystemStatus status)
{
    QString imageResource = getSubsystemStatusImage(status);
    m_ui->labelFPVLED->setPixmap(QPixmap(imageResource));
}

void MainWindow::steeringStatus(SubsystemStatus status)
{
    QString imageResource = getSubsystemStatusImage(status);
    m_ui->labelSteeringLED->setPixmap(QPixmap(imageResource));
}

void MainWindow::emulatorStatus(SubsystemStatus status)
{
    QString imageResource = getSubsystemStatusImage(status);
    m_ui->labelEmulatorLED->setPixmap(QPixmap(imageResource));
}

void MainWindow::keyAssigning(bool enabled)
{
    if (enabled) {
        // Disable passing key events to steering controller.
        disconnect(&m_padDriver, SIGNAL(padControllerAxisPressed(int,int)), &m_steeringController, SLOT(handleAxisEvent(int,int)));
        disconnect(&m_padDriver, SIGNAL(padControllerButtonPressed(int,bool)), &m_steeringController, SLOT(handleButtonEvent(int,bool)));

        connect(&m_padDriver, SIGNAL(padControllerAxisPressed(int,int)), m_settingsWidget, SLOT(setPadAxisMapping(int,int)));
        connect(&m_padDriver, SIGNAL(padControllerButtonPressed(int,bool)), m_settingsWidget, SLOT(setPadButtonMapping(int,bool)));
    }
    else {
        disconnect(&m_padDriver, SIGNAL(padControllerAxisPressed(int,int)), m_settingsWidget, SLOT(setPadAxisMapping(int,int)));
        disconnect(&m_padDriver, SIGNAL(padControllerButtonPressed(int,bool)), m_settingsWidget, SLOT(setPadButtonMapping(int,bool)));

        // Enable passing key events to steering controller.
        connect(&m_padDriver, SIGNAL(padControllerAxisPressed(int,int)), &m_steeringController, SLOT(handleAxisEvent(int,int)));
        connect(&m_padDriver, SIGNAL(padControllerButtonPressed(int,bool)), &m_steeringController, SLOT(handleButtonEvent(int,bool)));
    }
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
    connect(m_ui->toolbarSettings, SIGNAL(triggered()), m_settingsWidget, SLOT(exec()));

    connect(&m_padDriver, SIGNAL(detectedPadController(QString)), m_settingsWidget, SLOT(setPadControllerName(QString)));
    connect(m_settingsWidget, SIGNAL(connectPadController(QString)), &m_padDriver, SLOT(connect(QString)));
    connect(m_settingsWidget, SIGNAL(padSensitivityChanged(int)), &m_padDriver, SLOT(setSensitivity(int)));
    connect(m_settingsWidget, SIGNAL(assignKeys(bool)), this, SLOT(keyAssigning(bool)));
    connect(m_settingsWidget, SIGNAL(registerAxisEvent(int,SteeringController::AxisSteeringEvent)), &m_steeringController, SLOT(registerAxisEvent(int,SteeringController::AxisSteeringEvent)));
    connect(m_settingsWidget, SIGNAL(registerButtonEvent(int,SteeringController::ButtonSteeringEvent)), &m_steeringController, SLOT(registerButtonEvent(int,SteeringController::ButtonSteeringEvent)));
    connect(&m_padDriver, SIGNAL(padControllerAxisPressed(int,int)), &m_steeringController, SLOT(handleAxisEvent(int,int)));
    connect(&m_padDriver, SIGNAL(padControllerButtonPressed(int,bool)), &m_steeringController, SLOT(handleButtonEvent(int,bool)));

    // This trick will place settings toolbar action at the bottom.
    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_ui->toolBarMain->addWidget(spacer);
    m_ui->toolBarMain->addAction(m_ui->toolbarSettings);
}

void MainWindow::initCentralWidgets()
{
    m_settingsWidget = new SettingsDialog(this);
    m_consoleLogsWidget = new ConsoleLogsWidget();
    m_googleMapsView = new GoogleMapsView();
    m_telemetryTabWidget = new TelemetryTabWidget();
    m_fpvView = new FPVView();
    m_systemInfoWidget = new SystemInfoWidget();
    m_alertsWidget = new AlertsWidget();
    m_cocpitConsoleWidget = new CocpitConsoleWidget();
    m_emulatorWidget = new EmulatorWidget();

    connect(m_settingsWidget, SIGNAL(logsStarted(bool)), m_consoleLogsWidget, SLOT(setOperating(bool)));
    connect(m_settingsWidget, SIGNAL(commandsStarted(bool)), &m_commandsManager, SLOT(setOperating(bool)));
    connect(m_consoleLogsWidget, SIGNAL(logsStatus(SubsystemStatus)), this, SLOT(logsStatus(SubsystemStatus)));
    connect(&m_commandsManager, SIGNAL(geolocationStatus(SubsystemStatus)), this, SLOT(geolocationStatus(SubsystemStatus)));
    connect(&m_commandsManager, SIGNAL(telemetryStatus(SubsystemStatus)), this, SLOT(telemetryStatus(SubsystemStatus)));
    connect(&m_commandsManager, SIGNAL(fpvStatus(SubsystemStatus)), this, SLOT(fpvStatus(SubsystemStatus)));
    connect(&m_commandsManager, SIGNAL(steeringStatus(SubsystemStatus)), this, SLOT(steeringStatus(SubsystemStatus)));
    connect(&m_commandsManager, SIGNAL(emulatorStatus(SubsystemStatus)), this, SLOT(emulatorStatus(SubsystemStatus)));

    setCentralView(CENTRAL_VIEW_LOGS);
    m_ui->toolbarLogs->setChecked(true);
}

void MainWindow::setCentralView(CentralView centralView)
{
    if (centralWidget()) {
        // This prevents QMainWindow from deleting central widget (because it takes ownership of it).
        centralWidget()->setParent(nullptr);
    }

    switch (centralView) {
    case CENTRAL_VIEW_LOGS:
        m_ui->lineEdit->setText("Logs");
        setCentralWidget(m_consoleLogsWidget);
        break;
    case CENTRAL_VIEW_GEOLOCATION:
        m_ui->lineEdit->setText("Geolocation");
        setCentralWidget(m_googleMapsView);
        break;
    case CENTRAL_VIEW_TELEMETRY:
        m_ui->lineEdit->setText("Telemetry");
        setCentralWidget(m_telemetryTabWidget);
        break;
    case CENTRAL_VIEW_FPV:
        m_ui->lineEdit->setText("FPV");
        setCentralWidget(m_fpvView);
        break;
    case CENTRAL_VIEW_SYSTEM_INFO:
        m_ui->lineEdit->setText("System Info");
        setCentralWidget(m_systemInfoWidget);
        break;
    case CENTRAL_VIEW_ALERTS:
        m_ui->lineEdit->setText("Alerts");
        setCentralWidget(m_alertsWidget);
        break;
    case CENTRAL_VIEW_STEERING:
        m_ui->lineEdit->setText("Steering");
        setCentralWidget(m_cocpitConsoleWidget);
        break;
    case CENTRAL_VIEW_EMULATOR:
        m_ui->lineEdit->setText("Emulator");
        setCentralWidget(m_emulatorWidget);
        break;
    default:
        break;
    }
}

QString MainWindow::getSubsystemStatusImage(SubsystemStatus status)
{
    switch (status) {
    case SUBSYSTEM_DISABLED:    return ":/Icons/Icons/led-off.png";
    case SUBSYSTEM_ENABLED:     return ":/Icons/Icons/led-red.png";
    case SUBSYSTEM_CONNECTED:   return ":/Icons/Icons/led-green.png";
    }

    return "";
}
