////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       06.02.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef EMULATORDOCKWIDGET_H
#define EMULATORDOCKWIDGET_H

#include <QDockWidget>

namespace Ui {
    class EmulatorDockWidget;
}

class EmulatorDockWidget : public QDockWidget {
    Q_OBJECT

public:
    explicit EmulatorDockWidget(QWidget* parent = 0);
    virtual ~EmulatorDockWidget();

private:
    Ui::EmulatorDockWidget* m_ui;
};

#endif
