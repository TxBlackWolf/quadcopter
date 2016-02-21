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
                Core/AlertsWidget.cpp \
                Core/CocpitConsoleWidget.cpp \
                Core/ConsoleLogsWidget.cpp \
                Core/EmulatorWidget.cpp \
                Core/FPVView.cpp \
                Core/GoogleMapsView.cpp \
                Core/SettingsDialog.cpp \
                Core/SystemInfoWidget.cpp \
                Core/TelemetryTabWidget.cpp \
                Misc/AboutDialog.cpp \
                Tools/Options/EmulatorOptions.cpp \
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
                Core/AlertsWidget.h \
                Core/CocpitConsoleWidget.h \
                Core/ConsoleLogsWidget.h \
                Core/EmulatorWidget.h \
                Core/FPVView.h \
                Core/GoogleMapsView.h \
                Core/SettingsDialog.h \
                Core/SystemInfoWidget.h \
                Core/TelemetryTabWidget.h \
                Misc/AboutDialog.h \
                Misc/SubsystemsStatus.h \
                Misc/Version.h \
                Tools/Options/EmulatorOptions.h \
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
                Core/AlertsWidget.ui \
                Core/CocpitConsoleWidget.ui \
                Core/ConsoleLogsWidget.ui \
                Core/EmulatorWidget.ui \
                Core/FPVView.ui \
                Core/GoogleMapsView.ui \
                Core/SettingsDialog.ui \
                Core/SystemInfoWidget.ui \
                Core/TelemetryTabWidget.ui \
                Misc/AboutDialog.ui

RESOURCES       += resources.qrc
