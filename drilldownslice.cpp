#include "drilldownslice.h"

QT_CHARTS_USE_NAMESPACE

DrillDownSlice::DrillDownSlice(qreal value, QString prefix, QAbstractSeries *drilldownSeries)
    : m_drilldownSeries(drilldownSeries),
      m_prefix(prefix)
{
    setValue(value);
    updateLabel();
    setLabelFont(QFont("Arial", 8));
    connect(this, &DrillDownSlice::percentageChanged, this, &DrillDownSlice::updateLabel);
    connect(this, &DrillDownSlice::hovered, this, &DrillDownSlice::showHighlight);
}

DrillDownSlice::~DrillDownSlice()
{

}

QAbstractSeries *DrillDownSlice::drilldownSeries() const
{
    return m_drilldownSeries;
}

void DrillDownSlice::updateLabel()
{
    QString label = m_prefix;
    label += " $";
    label += QString::number(value());
    label += ", ";
    label += QString::number(percentage() * 100, 'f', 1);
    label += "%";
    setLabel(label);
}

void DrillDownSlice::showHighlight(bool show)
{
    setLabelVisible(show);
    setExploded(show);
}
