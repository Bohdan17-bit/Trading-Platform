#include "drilldownchart.h"
#include "drilldownslice.h"

QT_CHARTS_USE_NAMESPACE

DrillDownChart::DrillDownChart(QGraphicsItem *parent, Qt::WindowFlags wFlags)
    : QChart(QChart::ChartTypeCartesian, parent, wFlags),
      m_currentSeries(0)
{

}

DrillDownChart::~DrillDownChart()
{

}

void DrillDownChart::changeSeries(QAbstractSeries *series)
{
    if(m_currentSeries)
        removeSeries(m_currentSeries);
    m_currentSeries = series;
    addSeries(series);
    setTitle(series->name());
}

void DrillDownChart::handleSliceClicked(QPieSlice *slice)
{
    DrillDownSlice *drilldownSlice = static_cast<DrillDownSlice* >(slice);
    changeSeries(drilldownSlice->drilldownSeries());
}
