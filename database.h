#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QPair>
#include <QVector>

class Database
{
public:
    static void initDatabase();
    static void openDatabase();

    static bool userIsExist(QString user_name);
    static bool accountIsCreated(QString user_name);
    static void createEmptyFieldsPortfolio(QString user_name);

    static bool rewriteBalance(QString user_name, double balance);

    static bool writeRecordToHistory(QString user_name, QString action, QString name_cryptocurrency, double number_cryptocurrency, double price, double usd);

    static bool updateNumberCryptocurrencyPlus(QString user_name, double number, QString crypto_name);
    static bool updateNumberCryptocurrencyMinus(QString user_name, double number, QString crypto_name);

    static double getNumberCryptocurrency(QString user_name, QString crypto_name);
    static double getBalance(QString user_name);
    static double getBalanceInCryptocurrrency(QString user_name);

    static QVector<QPair<QString, double>> getNumberAllCryptocurrencies(QString user_name);

private:
    Database(){};
    static QSqlDatabase db;
    static void createFields(QSqlQuery query);
};

#endif // DATABASE_H
