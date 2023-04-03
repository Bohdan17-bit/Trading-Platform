#include "candlesticklistbuilder.h"


QList<QtCharts::QCandlestickSet*> CandleStickListBuilder::get_list_candlestick()
{
    QList<QtCharts::QCandlestickSet*> list;
    QJsonArray jsonArray = apiServiceResponse.get_response().array();
    foreach(const QJsonValue &value, jsonArray)
    {
        QJsonArray nested_json = value.toArray();
        qreal low = nested_json.at(0).toString().toDouble();
        qreal high = nested_json.at(1).toString().toDouble();
        qreal open = nested_json.at(2).toString().toDouble();
        qreal close = nested_json.at(3).toString().toDouble();
        qreal date = nested_json.at(12).toDouble();
        list.append(this->createCandleStickSet(date, open, close, low, high));
        qDebug() << list.size();
    }
    return list;
}
