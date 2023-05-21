#include "apiaddressbuilder.h"


QString ApiAddressBuilder::getChartData(QString currency_pair, QString period, QString limit)
{
    return base_api + currency_pair + QString("/candles?")
            + QString("interval=") + period
            + QString("&limit=")
            + limit;
}


QString ApiAddressBuilder::getPriceCryptoPair(QString pair)
{
    return base_api + pair + QString("/markPrice");
}


QString ApiAddressBuilder::getDataAllCryptoPairs()
{
    return base_api + QString("price");
}
