//=============================================================================================
//
// Filename   : MainWindow.h
// Author     : Kuba Sejdak
// Created on : 28.11.2014
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//=============================================================================================

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Toolbar/Alerts/AlertsDockWidget.h"
#include "Toolbar/FPV/FPVDockWidget.h"
#include "Toolbar/Geolocation/GeolocationDockWidget.h"
#include "Toolbar/Logs/LogsDockWidget.h"
#include "Toolbar/Logs/ConsoleLogsWidget.h"
#include "Toolbar/SystemInfo/SystemInfoDockWidget.h"
#include "Toolbar/Telemetry/TelemetryDockWidget.h"

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
        CENTRAL_VIEW_ALERTS
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
    TelemetryDockWidget* m_telemetryDockWidget;
    FPVDockWidget* m_fpvDockWidget;
    SystemInfoDockWidget* m_systemInfoDockWidget;
    AlertsDockWidget* m_alertsDockWidget;
};

#endif
