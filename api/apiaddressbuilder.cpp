#include "apiaddressbuilder.h"


QString ApiAddressBuilder::getChartData(QString currency_pair, QString period, QString limit)
{
    return QString("https://api.poloniex.com/markets/") + currency_pair + QString("/candles?")
            + QString("interval=") + period
            + QString("&limit=")
            + limit;
}


QString ApiAddressBuilder::getPriceCryptoPair(QString pair)
{
    return QString("https://api.poloniex.com/markets/") + pair + QString("/markPrice");
}


QString ApiAddressBuilder::getDataAllCryptoPairs()
{
    QString("https://api.poloniex.com/markets/") + QString("price");
}
