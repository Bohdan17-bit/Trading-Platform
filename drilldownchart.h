#ifndef DRILLDOWNCHART_H
#define DRILLDOWNCHART_H

#include <QtCharts/QChart>

QT_CHARTS_BEGIN_NAMESPACE
class QAbstractSeries;
class QPieSlice;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class DrillDownChart : public QChart
{
    Q_OBJECT
public:
    explicit DrillDownChart(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = {});
    ~DrillDownChart();
    void changeSeries(QAbstractSeries *series);

public slots:
    void handleSliceClicked(QPieSlice *slice);

private:
    QAbstractSeries *m_currentSeries;
};

#endif // DRILLDOWNCHART_H
