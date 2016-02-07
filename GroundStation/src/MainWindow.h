////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       28.11.2014
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Core/Alerts/AlertsDockWidget.h"
#include "Core/Emulator/EmulatorDockWidget.h"
#include "Core/Emulator/EmulatorTabWidget.h"
#include "Core/FPV/FPVDockWidget.h"
#include "Core/Geolocation/GeolocationDockWidget.h"
#include "Core/Geolocation/GoogleMapsView.h"
#include "Core/Logs/LogsDockWidget.h"
#include "Core/Logs/ConsoleLogsWidget.h"
#include "Core/Steering/CocpitConsoleWidget.h"
#include "Core/Steering/SteeringDockWidget.h"
#include "Core/SystemInfo/SystemInfoDockWidget.h"
#include "Core/SystemInfo/SystemInfoWidget.h"
#include "Core/Telemetry/TelemetryDockWidget.h"
#include "Core/Telemetry/TelemetryTabWidget.h"
#include "Misc/SubsystemsStatus.h"

#include <QActionGroup>
#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

    enum CentralView {
        CENTRAL_VIEW_UNKNOWN,
        CENTRAL_VIEW_LOGS,
        CENTRAL_VIEW_GEOLOCATION,
        CENTRAL_VIEW_TELEMETRY,
        CENTRAL_VIEW_FPV,
        CENTRAL_VIEW_SYSTEM_INFO,
        CENTRAL_VIEW_ALERTS,
        CENTRAL_VIEW_STEERING,
        CENTRAL_VIEW_EMULATOR
    };

public:
    explicit MainWindow(QWidget* parent = 0);
    virtual ~MainWindow();

public slots:
    void toolbarLogsClicked();
    void toolbarGeolocationClicked();
    void toolbarTelemetryClicked();
    void toolbarFPVClicked();
    void toolbarSystemInfoClicked();
    void toolbarAlertsClicked();
    void toolbarSteeringClicked();
    void toolbarEmulatorClicked();
    void logsStatus(SubsystemStatus status);
    void geolocationStatus(SubsystemStatus status);
    void telemetryStatus(SubsystemStatus status);
    void fpvStatus(SubsystemStatus status);
    void steeringStatus(SubsystemStatus status);
    void emulatorStatus(SubsystemStatus status);

private:
    void init();
    void initTopDockWidgets();
    void initCentralWidgets();

    void setCentralView(CentralView centralView);

private:
    Ui::MainWindow* m_ui;
    QActionGroup* m_actionGroup;
    QDockWidget* m_currentTopDockWidget;

    LogsDockWidget* m_logsDockWidget;
    ConsoleLogsWidget* m_consoleLogsWidget;

    GeolocationDockWidget* m_geolocationDockWidget;
    GoogleMapsView *m_googleMapsView;

    TelemetryDockWidget* m_telemetryDockWidget;
    TelemetryTabWidget* m_telemetryTabWidget;

    FPVDockWidget* m_fpvDockWidget;

    SystemInfoDockWidget* m_systemInfoDockWidget;
    SystemInfoWidget* m_systemInfoWidget;

    AlertsDockWidget* m_alertsDockWidget;

    SteeringDockWidget* m_steeringDockWidget;
    CocpitConsoleWidget* m_cocpitConsoleWidget;

    EmulatorDockWidget* m_emulatorDockWidget;
    EmulatorTabWidget* m_emulatorTabWidget;
};

#endif
