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
#include <qwt_plot_grid.h>

namespace Ui {
    class TelemetryTabWidget;
}

class TelemetryTabWidget : public QTabWidget {
    Q_OBJECT

public:
    explicit TelemetryTabWidget(QWidget* parent = nullptr);
    virtual ~TelemetryTabWidget();

private:
    void init();
    void clear();

private slots:
    void onClearButtonClicked();

private:
    Ui::TelemetryTabWidget* m_ui;

    QwtPlotGrid* m_plotGridFrontLeft;
    QwtPlotGrid* m_plotGridFrontRight;
    QwtPlotGrid* m_plotGridRearLeft;
    QwtPlotGrid* m_plotGridRearRight;
};

#endif
