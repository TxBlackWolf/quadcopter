////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       11.02.2015
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef TELEMETRYDOCKWIDGET_H
#define TELEMETRYDOCKWIDGET_H

#include <QDockWidget>

namespace Ui
{
    class TelemetryDockWidget;
}

class TelemetryDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit TelemetryDockWidget(QWidget* parent = 0);
    ~TelemetryDockWidget();

private:
    Ui::TelemetryDockWidget* m_ui;
};

#endif
