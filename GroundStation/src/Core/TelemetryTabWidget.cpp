////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       23.03.2015
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "TelemetryTabWidget.h"
#include "ui_TelemetryTabWidget.h"

#include <QList>
#include <QTreeWidgetItem>
#include <qwt_plot.h>

TelemetryTabWidget::TelemetryTabWidget(QWidget* parent)
    : QTabWidget(parent)
    , m_ui(new Ui::TelemetryTabWidget())
    , m_plotGridFrontLeft(new QwtPlotGrid())
    , m_plotGridFrontRight(new QwtPlotGrid())
    , m_plotGridRearLeft(new QwtPlotGrid())
    , m_plotGridRearRight(new QwtPlotGrid())
{
    m_ui->setupUi(this);

    init();
    connect(m_ui->buttonClear, SIGNAL(clicked()), this, SLOT(onClearButtonClicked()));
}

TelemetryTabWidget::~TelemetryTabWidget()
{
    clear();

    delete m_ui;
    delete m_plotGridFrontLeft;
    delete m_plotGridFrontRight;
    delete m_plotGridRearLeft;
    delete m_plotGridRearRight;
}

void TelemetryTabWidget::init()
{
    // Front left plot.
    m_ui->frontLeftEnginePlot->setTitle("Front left engine");
    m_ui->frontLeftEnginePlot->setAxisScale(QwtPlot::yLeft, 0, 100, 10);
    m_ui->frontLeftEnginePlot->setAxisMaxMinor(QwtPlot::yLeft, 2);
    m_ui->frontLeftEnginePlot->setAxisTitle(QwtPlot::yLeft, "Throttle [%]");
    m_ui->frontLeftEnginePlot->setAxisScale(QwtPlot::xBottom, 0, 200, 10);
    m_ui->frontLeftEnginePlot->setAxisTitle(QwtPlot::xBottom, "Time [s]");
    m_plotGridFrontLeft->setYAxis(QwtPlot::yLeft);
    m_plotGridFrontLeft->setPen(QColor(60, 60, 60), 0.0, Qt::DashLine);
    m_plotGridFrontLeft->enableY(true);
    m_plotGridFrontLeft->enableYMin(true);
    m_plotGridFrontLeft->enableX(false);
    m_plotGridFrontLeft->enableXMin(false);
    m_plotGridFrontLeft->attach(m_ui->frontLeftEnginePlot);

    // Front right plot.
    m_ui->frontRightEnginePlot->setTitle("Front right engine");
    m_ui->frontRightEnginePlot->setAxisScale(QwtPlot::yLeft, 0, 100, 10);
    m_ui->frontRightEnginePlot->setAxisMaxMinor(QwtPlot::yLeft, 2);
    m_ui->frontRightEnginePlot->setAxisTitle(QwtPlot::yLeft, "Throttle [%]");
    m_ui->frontRightEnginePlot->setAxisScale(QwtPlot::xBottom, 0, 200, 10);
    m_ui->frontRightEnginePlot->setAxisTitle(QwtPlot::xBottom, "Time [s]");
    m_plotGridFrontRight->setYAxis(QwtPlot::yLeft);
    m_plotGridFrontRight->setPen(QColor(60, 60, 60), 0.0, Qt::DashLine);
    m_plotGridFrontRight->enableY(true);
    m_plotGridFrontRight->enableYMin(true);
    m_plotGridFrontRight->enableX(false);
    m_plotGridFrontRight->enableXMin(false);
    m_plotGridFrontRight->attach(m_ui->frontRightEnginePlot);

    // Rear left plot.
    m_ui->rearLeftEnginePlot->setTitle("Rear left engine");
    m_ui->rearLeftEnginePlot->setAxisScale(QwtPlot::yLeft, 0, 100, 10);
    m_ui->rearLeftEnginePlot->setAxisMaxMinor(QwtPlot::yLeft, 2);
    m_ui->rearLeftEnginePlot->setAxisTitle(QwtPlot::yLeft, "Throttle [%]");
    m_ui->rearLeftEnginePlot->setAxisScale(QwtPlot::xBottom, 0, 200, 10);
    m_ui->rearLeftEnginePlot->setAxisTitle(QwtPlot::xBottom, "Time [s]");
    m_plotGridRearLeft->setYAxis(QwtPlot::yLeft);
    m_plotGridRearLeft->setPen(QColor(60, 60, 60), 0.0, Qt::DashLine);
    m_plotGridRearLeft->enableY(true);
    m_plotGridRearLeft->enableYMin(true);
    m_plotGridRearLeft->enableX(false);
    m_plotGridRearLeft->enableXMin(false);
    m_plotGridRearLeft->attach(m_ui->rearLeftEnginePlot);

    // Rear right plot.
    m_ui->rearRightEnginePlot->setTitle("Rear right engine");
    m_ui->rearRightEnginePlot->setAxisScale(QwtPlot::yLeft, 0, 100, 10);
    m_ui->rearRightEnginePlot->setAxisMaxMinor(QwtPlot::yLeft, 2);
    m_ui->rearRightEnginePlot->setAxisTitle(QwtPlot::yLeft, "Throttle [%]");
    m_ui->rearRightEnginePlot->setAxisScale(QwtPlot::xBottom, 0, 200, 10);
    m_ui->rearRightEnginePlot->setAxisTitle(QwtPlot::xBottom, "Time [s]");
    m_plotGridRearRight->setYAxis(QwtPlot::yLeft);
    m_plotGridRearRight->setPen(QColor(60, 60, 60), 0.0, Qt::DashLine);
    m_plotGridRearRight->enableY(true);
    m_plotGridRearRight->enableYMin(true);
    m_plotGridRearRight->enableX(false);
    m_plotGridRearRight->enableXMin(false);
    m_plotGridRearRight->attach(m_ui->rearRightEnginePlot);
}

void TelemetryTabWidget::clear()
{
    m_ui->treeWidget->clear();
}

void TelemetryTabWidget::onClearButtonClicked()
{
    clear();
}
