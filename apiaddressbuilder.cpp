#include "apiaddressbuilder.h"


QString ApiAddressBuilder::getChartData(QString currency_pair, QString start, QString end, QString period)
{
    return QString("https://poloniex.com/public?") + QString("command=") + QString("returnChartData")
           + "&currencyPair=" + currency_pair
           + "&start=" + start
           + "&end=" + end
           + "&period=" + period;
}


QString ApiAddressBuilder::getTicker()
{
    return QString("https://poloniex.com/public?") + QString("command=") + QString("returnTicker");
}


QString ApiAddressBuilder::getDataCryptoPair(QString pair)
{
    return QString("https://api.poloniex.com/") + QString("markets/") + pair + QString("/markPrice");
}
