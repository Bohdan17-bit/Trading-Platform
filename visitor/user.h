#ifndef USER_H
#define USER_H

#include <QString>
#include <QPair>
#include <QVector>
#include "storage/database.h"
#include <cmath>

class User
{
private:

    double balance_usd;
    QString user_name;
    QVector<QPair<QString, double>> coins_list;

    void loadCoinsList();
    void updateBalanceUsd(double new_balance);
    void updateNumberOfCoin(QString coin_name, double new_value);

public:

    User()
    {

    };

    QString discoverName();
    double discoverBalance();
    QVector<QPair<QString, double>> getCoinsList();

    bool createNewUser(QString user_name);
    bool userIsExists(QString user_name);

    void loadUserData();
    void setUsername(QString user_name);
    void saveTransaction(QString action_name, QString name_cryptocurrency, double number_cryptocurrency, double price, double total_usd);

    void buyCoin(QString name_cryptocurrency, double number_cryptocurrency, double price, double total_usd);
    void sellCoin(QString name_cryptocurrency, double number_cryptocurrency, double price, double total_usd);

    bool HaveEnoughCoins(QString name_coin, double value);
    bool HaveEnoughMoney(double value);

    double getNumberOfCoin(QString name_coin);
};

#endif // USER_H
