#include "moneyconverter.h"
#include <QString>
#include <QDebug>

int MoneyConverter::numberToMultiply(int precision)
{
    int number = 1;
    for(int i = 0; i < precision; i++)
    {
        number *= 10;
    }
    return number;
}

 int MoneyConverter::doubleCryptoToInteger(double number)
 {
     double temp = QString::number(number, 'f', PRECISION_COINS).toDouble();
     return temp * numberToMultiply(PRECISION_COINS);
 }

 double MoneyConverter::integerCryptoToDouble(int number)
 {
     return static_cast<double>(number) / numberToMultiply(PRECISION_COINS);
 }

 double MoneyConverter::integerUsdToDouble(int usd)
 {
     return static_cast<double>(usd) / numberToMultiply(PRECISION_USD);
 }

 int MoneyConverter::doubleUsdToInteger(double usd)
 {
     return usd * numberToMultiply(PRECISION_USD);
 }
