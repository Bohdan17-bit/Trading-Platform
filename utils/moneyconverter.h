#ifndef MONEYCONVERTER_H
#define MONEYCONVERTER_H


class MoneyConverter
{
private:
    MoneyConverter();   // 5 знаків після крапки для монет та 2 знаки для доларів

    static const int PRECISION_USD = 2;
    static const int PRECISION_COINS = 3;

    static int numberToMultiply(int precision);

public:
    static int doubleCryptoToInteger(double number);
    static double integerCryptoToDouble(int number);

    static int doubleUsdToInteger(double usd);
    static double integerUsdToDouble(int usd);
};

#endif // MONEYCONVERTER_H
