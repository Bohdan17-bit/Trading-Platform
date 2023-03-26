#ifndef CANDLESTICKLIST_H
#define CANDLESTICKLIST_H

#include <QJsonDocument>
#include <QtCharts>

class CandleStickList
{
public:
    virtual ~CandleStickList() = default;
    virtual QList<QtCharts::QCandlestickSet*> get_list_candlestick();
    QtCharts::QCandlestickSet* createCandleStickSet(qreal timestamp, qreal open, qreal close, qreal low, qreal high);
};

#endif // CANDLESTICKLIST_H
