////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       11.02.2015
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef SYSTEMINFODOCKWIDGET_H
#define SYSTEMINFODOCKWIDGET_H

#include <QDockWidget>

namespace Ui {
    class SystemInfoDockWidget;
}

class SystemInfoDockWidget : public QDockWidget {
    Q_OBJECT

public:
    explicit SystemInfoDockWidget(QWidget* parent = 0);
    ~SystemInfoDockWidget();

private:
    Ui::SystemInfoDockWidget* m_ui;
};

#endif
