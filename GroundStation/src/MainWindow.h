//============================================================================
//
// Filename   : MainWindow.h
// Author     : Kuba Sejdak
// Created on : 28 lis 2014
//
//============================================================================

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Toolbar/Logs/LogsDockWidget.h"
#include "Toolbar/Logs/ConsoleLogsWidget.h"
#include "Toolbar/Geolocation/GeolocationDockWidget.h"
#include "Toolbar/FPV/FPVDockWidget.h"
#include "Toolbar/SystemInfo/SystemInfoDockWidget.h"
#include "Toolbar/Alerts/AlertsDockWidget.h"

#include <QMainWindow>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum CentralView
    {
        CENTRAL_VIEW_UNKNOWN,
        CENTRAL_VIEW_LOGS,
        CENTRAL_VIEW_GEOLOCATION,
        CENTRAL_VIEW_FPV,
        CENTRAL_VIEW_SYSTEM_INFO,
        CENTRAL_VIEW_ALERTS
    };

public:
    /// @brief Constructor.
    /// @param [in] parent      parent widget
    explicit MainWindow(QWidget* parent = 0);

    /// @brief Virtual destructor.
    virtual ~MainWindow();

public slots:
    void toolbarLogsClicked();
    void toolbarGeolocationClicked();
    void toolbarFPVClicked();
    void toolbarSystemInfoClicked();
    void toolbarAlertsClicked();

private:
    void setCentralView(CentralView centralView);

    /// @brief Initializes main window.
    void init();

    /// @brief Initialized top dock widgets
    void initTopDockWidgets();

    /// @brief Initializes all central widgets.
    void initCentralWidgets();

private:
    Ui::MainWindow* m_ui;

    /// @brief Log widgets.
    LogsDockWidget* m_logsDockWidget;
    ConsoleLogsWidget* m_consoleLogsWidget;

    /// @brief Geolocation widgets.
    GeolocationDockWidget* m_geolocationDockWidget;

    /// @brief FPV widgets.
    FPVDockWidget* m_fpvDockWidget;

    /// @brief System info widgets.
    SystemInfoDockWidget* m_systemInfoDockWidget;

    /// @brief Alerts widgets.
    AlertsDockWidget* m_alertsDockWidget;

    CentralView m_centralView;
    QAction *m_currentlySelectedToolbar;
    QDockWidget* m_currentTopDockWidget;
};

#endif
