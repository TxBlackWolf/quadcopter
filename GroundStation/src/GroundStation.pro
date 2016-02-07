#-------------------------------------------------
#
# Project created by QtCreator 2014-11-26T23:33:34
#
#-------------------------------------------------

QT              += core gui serialport webkitwidgets
CONFIG          += c++11 qwt

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET          = GroundStation
TEMPLATE        = app
RC_FILE         = GroundStation.rc

CONFIG(debug, debug|release) {
    DESTDIR     = $$PWD/../bin/Debug
    OBJECTS_DIR = $$PWD/../build/Debug/obj
    MOC_DIR     = $$PWD/../build/Debug/moc
    RCC_DIR     = $$PWD/../build/Debug/rcc
    UI_DIR      = $$PWD/../build/Debug/ui
}
else {
    DESTDIR     = $$PWD/../bin/Release
    OBJECTS_DIR = $$PWD/../build/Release/obj
    MOC_DIR     = $$PWD/../build/Release/moc
    RCC_DIR     = $$PWD/../build/Release/rcc
    UI_DIR      = $$PWD/../build/Release/ui
}

Release:DESTDIR = $$PWD/../bin/Release

INCLUDEPATH     += $$PWD/../.. $$PWD/.

SOURCES         += main.cpp \
                MainWindow.cpp \
                Core/Alerts/AlertsDockWidget.cpp \
                Core/Emulator/EmulatorDockWidget.cpp \
                Core/Emulator/EmulatorTabWidget.cpp \
                Core/FPV/FPVDockWidget.cpp \
                Core/Geolocation/GeolocationDockWidget.cpp \
                Core/Geolocation/GoogleMapsView.cpp \
                Core/Logs/ConsoleLogsWidget.cpp \
                Core/Logs/LogsDockWidget.cpp \
                Core/Logs/LogsOptionsDialog.cpp \
                Core/Steering/CocpitConsoleWidget.cpp \
                Core/Steering/SteeringDockWidget.cpp \
                Core/SystemInfo/SystemInfoDockWidget.cpp \
                Core/SystemInfo/SystemInfoWidget.cpp \
                Core/Telemetry/TelemetryDockWidget.cpp \
                Core/Telemetry/TelemetryTabWidget.cpp \
                Misc/AboutDialog.cpp \
                Tools/Options/LogsOptions.cpp \
                Tools/Options/NetworkServerOptions.cpp \
                Tools/Options/SerialPortOptions.cpp \
                ../../common/commands/commands.c \
                ../../common/commands/control.c \
                ../../common/commands/debug_info.c \
                ../../common/commands/emulator.c \
                ../../common/commands/system_status.c \
                ../../common/commands/telemetry.c

HEADERS         += MainWindow.h \
                Core/Alerts/AlertsDockWidget.h \
                Core/Emulator/EmulatorDockWidget.h \
                Core/Emulator/EmulatorTabWidget.h \
                Core/FPV/FPVDockWidget.h \
                Core/Geolocation/GeolocationDockWidget.h \
                Core/Geolocation/GoogleMapsView.h \
                Core/Logs/ConsoleLogsWidget.h \
                Core/Logs/LogsDockWidget.h \
                Core/Logs/LogsOptionsDialog.h \
                Core/Steering/CocpitConsoleWidget.h \
                Core/Steering/SteeringDockWidget.h \
                Core/SystemInfo/SystemInfoDockWidget.h \
                Core/SystemInfo/SystemInfoWidget.h \
                Core/Telemetry/TelemetryDockWidget.h \
                Core/Telemetry/TelemetryTabWidget.h \
                Misc/AboutDialog.h \
                Misc/SubsystemsStatus.h \
                Misc/Version.h \
                Tools/Options/LogsOptions.h \
                Tools/Options/NetworkServerOptions.h \
                Tools/Options/SerialPortOptions.h \
                ../../common/commands/commands.h \
                ../../common/commands/control.h \
                ../../common/commands/debug_info.h \
                ../../common/commands/emulator.h \
                ../../common/commands/system_status.h \
                ../../common/commands/telemetry.h

FORMS           += MainWindow.ui \
                Core/Alerts/AlertsDockWidget.ui \
                Core/Emulator/EmulatorDockWidget.ui \
                Core/Emulator/EmulatorTabWidget.ui \
                Core/FPV/FPVDockWidget.ui \
                Core/Geolocation/GeolocationDockWidget.ui \
                Core/Geolocation/GoogleMapsView.ui \
                Core/Logs/LogsDockWidget.ui \
                Core/Logs/LogsOptionsDialog.ui \
                Core/Logs/ConsoleLogsWidget.ui \
                Core/Steering/CocpitConsoleWidget.ui \
                Core/Steering/SteeringDockWidget.ui \
                Core/SystemInfo/SystemInfoDockWidget.ui \
                Core/SystemInfo/SystemInfoWidget.ui \
                Core/Telemetry/TelemetryDockWidget.ui \
                Core/Telemetry/TelemetryTabWidget.ui \
                Misc/AboutDialog.ui

RESOURCES       += resources.qrc
