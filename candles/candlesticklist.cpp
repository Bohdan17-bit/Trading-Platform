#include "candlesticklist.h"


QtCharts::QCandlestickSet* CandleStickList::createCandleStickSet(qreal timestamp, qreal open, qreal close, qreal low, qreal high)
{
    QtCharts::QCandlestickSet * set = new QtCharts::QCandlestickSet(timestamp);
    set->setHigh(high);
    set->setLow(low);
    set->setOpen(open);
    set->setClose(close);
    return set;
}

QList<QtCharts::QCandlestickSet*> CandleStickList::get_list_candlestick()
{
    QList<QtCharts::QCandlestickSet*> list;
    list.append(createCandleStickSet(0, 0, 0, 0, 0)); // empty default candlestickset
    return list;
}
