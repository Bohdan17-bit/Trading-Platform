#ifndef APIADDRESSBUILDER_H
#define APIADDRESSBUILDER_H

#include <QString>
#include <ctime>
#include <QDebug>

class ApiAddressBuilder
{   
private:
    ApiAddressBuilder();
public:
    static QString getChartData(QString currency_pair, QString period, QString limit);
    static QString getPriceCryptoPair(QString pair);
    static QString getDataAllCryptoPairs();
};

#endif // APIADDRESSBUILDER_H
