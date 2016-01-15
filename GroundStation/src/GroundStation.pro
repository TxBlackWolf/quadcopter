#-------------------------------------------------
#
# Project created by QtCreator 2014-11-26T23:33:34
#
#-------------------------------------------------

QT              += core gui serialport
CONFIG          += c++11

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

LIBS            += -lboost_system -lboost_serialization

SOURCES         += main.cpp \
                MainWindow.cpp \
                Misc/AboutDialog.cpp \
                Toolbar/Alerts/AlertsDockWidget.cpp \
                Toolbar/FPV/FPVDockWidget.cpp \
                Toolbar/Geolocation/GeolocationDockWidget.cpp \
                Toolbar/Logs/ConsoleLogsWidget.cpp \
                Toolbar/Logs/LogsDockWidget.cpp \
                Toolbar/Logs/LogsOptionsDialog.cpp \
                Toolbar/SystemInfo/SystemInfoDockWidget.cpp \
                Toolbar/Telemetry/TelemetryDockWidget.cpp \
                Tools/Options.cpp

HEADERS         += MainWindow.h \
                Misc/AboutDialog.h \
                Misc/Version.h \
                Toolbar/Alerts/AlertsDockWidget.h \
                Toolbar/FPV/FPVDockWidget.h \
                Toolbar/Geolocation/GeolocationDockWidget.h \
                Toolbar/Logs/ConsoleLogsWidget.h \
                Toolbar/Logs/LogsDockWidget.h \
                Toolbar/Logs/LogsOptionsDialog.h \
                Toolbar/SystemInfo/SystemInfoDockWidget.h \
                Toolbar/Telemetry/TelemetryDockWidget.h \
                Tools/Options.h

FORMS           += MainWindow.ui \
                Misc/AboutDialog.ui \
                Toolbar/Alerts/AlertsDockWidget.ui \
                Toolbar/FPV/FPVDockWidget.ui \
                Toolbar/Geolocation/GeolocationDockWidget.ui \
                Toolbar/Logs/LogsDockWidget.ui \
                Toolbar/Logs/LogsOptionsDialog.ui \
                Toolbar/Logs/ConsoleLogsWidget.ui \
                Toolbar/SystemInfo/SystemInfoDockWidget.ui \
                Toolbar/Telemetry/TelemetryDockWidget.ui

RESOURCES       += resources.qrc
