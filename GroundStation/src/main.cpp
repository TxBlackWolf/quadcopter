////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       28.11.2014
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("SkyViper");
    QCoreApplication::setOrganizationDomain("skyviper.com");
    QCoreApplication::setApplicationName("GroundStation");

    QApplication app(argc, argv);
    MainWindow w;
    w.show();

    return app.exec();
}
