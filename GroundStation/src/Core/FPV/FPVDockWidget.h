////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       11.02.2015
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef FPVDOCKWIDGET_H
#define FPVDOCKWIDGET_H

#include <QDockWidget>

namespace Ui {
    class FPVDockWidget;
}

class FPVDockWidget : public QDockWidget {
    Q_OBJECT

public:
    explicit FPVDockWidget(QWidget* parent = 0);
    virtual ~FPVDockWidget();

private:
    Ui::FPVDockWidget* m_ui;
};

#endif
