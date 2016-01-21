////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       08.02.2015
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef LOGSDOCKWIDGET_H
#define LOGSDOCKWIDGET_H

#include <QDockWidget>

namespace Ui {
    class LogsDockWidget;
}

class LogsDockWidget : public QDockWidget {
    Q_OBJECT

public:
    explicit LogsDockWidget(QWidget* parent = 0);
    ~LogsDockWidget();

public slots:
    void showLoggingOptions();
    void init();

private:
    Ui::LogsDockWidget* m_ui;
};

#endif
