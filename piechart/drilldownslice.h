#ifndef DRILLDOWNSLICE_H
#define DRILLDOWNSLICE_H

#include <QtCharts/QPieSlice>

QT_CHARTS_BEGIN_NAMESPACE
class QAbstractSeries;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class DrillDownSlice : public QPieSlice
{
    Q_OBJECT
public:
    DrillDownSlice(qreal value, QString prefix, QAbstractSeries *drilldownSeries);
    virtual ~DrillDownSlice();
    QAbstractSeries *drilldownSeries() const;

public slots:
    void updateLabel();
    void showHighlight(bool show);

private:
    QAbstractSeries *m_drilldownSeries;
    QString m_prefix;
};

#endif // DRILLDOWNSLICE_H
