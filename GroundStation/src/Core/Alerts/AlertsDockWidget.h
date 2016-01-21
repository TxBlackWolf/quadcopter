////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       11.02.2015
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef ALERTSDOCKWIDGET_H
#define ALERTSDOCKWIDGET_H

#include <QDockWidget>

namespace Ui {
    class AlertsDockWidget;
}

class AlertsDockWidget : public QDockWidget {
    Q_OBJECT

public:
    explicit AlertsDockWidget(QWidget* parent = 0);
    ~AlertsDockWidget();

private:
    Ui::AlertsDockWidget* m_ui;
};

#endif
