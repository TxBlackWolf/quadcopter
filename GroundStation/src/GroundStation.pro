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
                Core/CommandsManager.cpp \
                Core/PadCalibrator.cpp \
                Core/PadDriver.cpp \
                Tools/IServer.cpp \
                Tools/SerialPortServer.cpp \
                Tools/TCPServer.cpp \
                Tools/Options/CommandsOptions.cpp \
                Tools/Options/LogsOptions.cpp \
                Tools/Options/Common/SerialPortOptions.cpp \
                Tools/Options/Common/ServerOptions.cpp \
                Tools/Options/Common/TCPOptions.cpp \
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
                ../../command/command_common.c \
                ../../command/command_control.c \
                ../../command/command_debugInfo.c \
                ../../command/command_decoder.c \
                ../../command/command_emulator.c \
                ../../command/command_encoder.c \
                ../../command/command_statistics.c \
                ../../command/command_systemStatus.c \
                ../../command/command_telemetry.c

HEADERS         += \
                Core/CommandsManager.h \
                Core/PadCalibrator.h \
                Core/PadDriver.h \
                Misc/SubsystemsStatus.h \
                Misc/Version.h \
                Tools/IServer.h \
                Tools/SerialPortServer.h \
                Tools/TCPServer.h \
                Tools/Options/CommandsOptions.h \
                Tools/Options/LogsOptions.h \
                Tools/Options/Common/SerialPortOptions.h \
                Tools/Options/Common/ServerOptions.h \
                Tools/Options/Common/TCPOptions.h \
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
                ../../command/command_common.h \
                ../../command/command_control.h \
                ../../command/command_debugInfo.h \
                ../../command/command_decoder.h \
                ../../command/command_emulator.h \
                ../../command/command_encoder.h \
                ../../command/command_statistics.h \
                ../../command/command_systemStatus.h \
                ../../command/command_telemetry.h

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
