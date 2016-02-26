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

SOURCES         += \
                main.cpp \
                Tools/Options/EmulatorOptions.cpp \
                Tools/Options/LogsOptions.cpp \
                Tools/Options/NetworkServerOptions.cpp \
                Tools/Options/SerialPortOptions.cpp \
                Windows/AboutDialog.cpp \
                Windows/AlertsWidget.cpp \
                Windows/CocpitConsoleWidget.cpp \
                Windows/ConsoleLogsWidget.cpp \
                Windows/EmulatorWidget.cpp \
                Windows/FPVView.cpp \
                Windows/GoogleMapsView.cpp \
                Windows/MainWindow.cpp \
                Windows/SettingsDialog.cpp \
                Windows/SystemInfoWidget.cpp \
                Windows/TelemetryTabWidget.cpp \
                ../../common/commands/commands.c \
                ../../common/commands/control.c \
                ../../common/commands/debug_info.c \
                ../../common/commands/emulator.c \
                ../../common/commands/system_status.c \
                ../../common/commands/telemetry.c

HEADERS         += \
                Misc/SubsystemsStatus.h \
                Misc/Version.h \
                Tools/Options/EmulatorOptions.h \
                Tools/Options/LogsOptions.h \
                Tools/Options/NetworkServerOptions.h \
                Tools/Options/SerialPortOptions.h \
                Windows/AboutDialog.h \
                Windows/AlertsWidget.h \
                Windows/CocpitConsoleWidget.h \
                Windows/ConsoleLogsWidget.h \
                Windows/EmulatorWidget.h \
                Windows/FPVView.h \
                Windows/GoogleMapsView.h \
                Windows/MainWindow.h \
                Windows/SettingsDialog.h \
                Windows/SystemInfoWidget.h \
                Windows/TelemetryTabWidget.h \
                ../../common/commands/commands.h \
                ../../common/commands/control.h \
                ../../common/commands/debug_info.h \
                ../../common/commands/emulator.h \
                ../../common/commands/system_status.h \
                ../../common/commands/telemetry.h

FORMS           += \
                Windows/AboutDialog.ui \
                Windows/AlertsWidget.ui \
                Windows/CocpitConsoleWidget.ui \
                Windows/ConsoleLogsWidget.ui \
                Windows/EmulatorWidget.ui \
                Windows/FPVView.ui \
                Windows/GoogleMapsView.ui \
                Windows/MainWindow.ui \
                Windows/SettingsDialog.ui \
                Windows/SystemInfoWidget.ui \
                Windows/TelemetryTabWidget.ui

RESOURCES       += resources.qrc
