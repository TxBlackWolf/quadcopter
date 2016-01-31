////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       23.03.2015
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef TELEMETRYTABWIDGET_H
#define TELEMETRYTABWIDGET_H

#include <QTabWidget>

namespace Ui {
    class TelemetryTabWidget;
}

class TelemetryTabWidget : public QTabWidget {
    Q_OBJECT

public:
    explicit TelemetryTabWidget(QWidget* parent = 0);
    virtual ~TelemetryTabWidget();

    void clear();

private slots:
    void onClearButtonClicked();

private:
    Ui::TelemetryTabWidget* m_ui;
};

#endif
