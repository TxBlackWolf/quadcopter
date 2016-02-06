////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       06.02.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef EMULATORTABWIDGET_H
#define EMULATORTABWIDGET_H

#include <QTabWidget>

namespace Ui {
    class EmulatorTabWidget;
}

class EmulatorTabWidget : public QTabWidget {
    Q_OBJECT

public:
    explicit EmulatorTabWidget(QWidget* parent = 0);
    virtual ~EmulatorTabWidget();

private:
    Ui::EmulatorTabWidget* m_ui;
};

#endif
