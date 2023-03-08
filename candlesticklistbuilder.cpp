#include "candlesticklistbuilder.h"


QList<QtCharts::QCandlestickSet*> CandleStickListBuilder::get_list_candlestick()
{
    QList<QtCharts::QCandlestickSet*> list;
    QJsonArray jsonArray = apiServiceResponse.get_response().array();
    foreach(const QJsonValue &value, jsonArray)
    {
        qreal date = value.toObject().value("date").toString().toDouble();
        qreal high = value.toObject().value("high").toString().toDouble();
        qreal low = value.toObject().value("low").toString().toDouble();
        qreal open = value.toObject().value("open").toString().toDouble();
        qreal close = value.toObject().value("close").toString().toDouble();
        list.append(this->createCandleStickSet(date, open, close, low, high));
    }
    return list;
}
