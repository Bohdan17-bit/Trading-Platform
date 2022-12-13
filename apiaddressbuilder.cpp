#include "apiaddressbuilder.h"


QString ApiAddressBuilder::getChartData(QString currency_pair, QString start, QString end, QString period)
{
    return QString("https://poloniex.com/public?") + QString("command=") + QString("returnChartData")
           + "&currencyPair=" + currency_pair
           + "&start=" + start
           + "&end=" + end
           + "&period=" + period;
}


QString ApiAddressBuilder::getPriceCryptoPair(QString pair)
{
    return QString("https://api.poloniex.com/") + QString("markets/") + pair + QString("/markPrice");
}


QString ApiAddressBuilder::getDataAllCryptoPairs()
{
    return QString("https://api.poloniex.com/") + QString("markets/") + QString("/price");
}
