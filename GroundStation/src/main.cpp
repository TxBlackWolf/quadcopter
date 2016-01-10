//============================================================================
//
// Filename   : main.cpp
// Author     : Kuba Sejdak
// Created on : 28 lis 2014
//
//============================================================================

#include "MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("ARMCopter");
    QCoreApplication::setOrganizationDomain("armcopter.com");
    QCoreApplication::setApplicationName("GroundStation");

    QApplication app(argc, argv);
    MainWindow w;
    w.show();

    return app.exec();
}
