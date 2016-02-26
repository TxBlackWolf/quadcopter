////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       06.02.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef COCPITCONSOLEWIDGET_H
#define COCPITCONSOLEWIDGET_H

#include <QWidget>

namespace Ui {
    class CocpitConsoleWidget;
}

class CocpitConsoleWidget : public QWidget {
    Q_OBJECT

public:
    explicit CocpitConsoleWidget(QWidget* parent = nullptr);
    virtual ~CocpitConsoleWidget();

private:
    Ui::CocpitConsoleWidget* m_ui;
};

#endif
