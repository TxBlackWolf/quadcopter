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

#include "AlertsWidget.h"
#include "CocpitConsoleWidget.h"
#include "ConsoleLogsWidget.h"
#include "EmulatorWidget.h"
#include "FPVView.h"
#include "GoogleMapsView.h"
#include "SettingsDialog.h"
#include "SystemInfoWidget.h"
#include "TelemetryTabWidget.h"
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
    explicit MainWindow(QWidget* parent = nullptr);
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
    void logsStatus(SubsystemStatus_t status);
    void geolocationStatus(SubsystemStatus_t status);
    void telemetryStatus(SubsystemStatus_t status);
    void fpvStatus(SubsystemStatus_t status);
    void steeringStatus(SubsystemStatus_t status);
    void emulatorStatus(SubsystemStatus_t status);

private:
    void init();
    void initCentralWidgets();

    void setCentralView(CentralView centralView);
    QString getSubsystemStatusImage(SubsystemStatus_t status);

private:
    Ui::MainWindow* m_ui;
    QActionGroup* m_actionGroup;
    SettingsDialog* m_settingsWidget;

    ConsoleLogsWidget* m_consoleLogsWidget;
    GoogleMapsView* m_googleMapsView;
    TelemetryTabWidget* m_telemetryTabWidget;
    FPVView* m_fpvView;
    SystemInfoWidget* m_systemInfoWidget;
    AlertsWidget* m_alertsWidget;
    CocpitConsoleWidget* m_cocpitConsoleWidget;
    EmulatorWidget* m_emulatorWidget;
};

#endif
