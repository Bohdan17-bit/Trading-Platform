#include "user.h"
#include <QDebug>

void User::loadUserData()
{
    balance_usd = Database::getBalance(user_name);
    loadCoinsList();
}

QString User::discoverName()
{
    return user_name;
}

double User::discoverBalance()
{
    return balance_usd;
    //return round(balance_usd * 100) / 100;
}

void User::loadCoinsList()
{
    coins_list = Database::getNumberAllCryptocurrencies(user_name);
}

void User::updateBalanceUsd(double new_balance)
{
    balance_usd = new_balance;
    Database::rewriteBalance(this->user_name, new_balance);
}

void User::setUsername(QString user_name)
{
    this->user_name = user_name;
}

void User::updateNumberOfCoin(QString coin_name, double new_value)
{
    for(int i = 0; i < this->coins_list.size(); i++)
    {
        if(coins_list[i].first == coin_name)
        {
            coins_list[i].second = new_value;
        }
    }
}

bool User::userIsExists(QString user_name)
{
    if(Database::userIsExist(user_name))
    {
        return true;
    }
    return false;
}

bool User::createNewUser(QString user_name)
{
    if(Database::accountIsCreated(user_name))
    {
        Database::createEmptyFieldsPortfolio(user_name);
        this->user_name = user_name;
        return true;
    }
    return false;
}

void User::saveTransaction(QString action_name, QString name_cryptocurrency, double number_cryptocurrency, double price, double total_usd)
{
    Database::writeRecordToHistory(user_name, action_name, name_cryptocurrency,number_cryptocurrency, price, total_usd);
}

void User::buyCoin(QString name_cryptocurrency, double number_cryptocurrency, double price, double total_usd)
{
    Database::updateNumberCryptocurrencyPlus(user_name, number_cryptocurrency, name_cryptocurrency);
    updateNumberOfCoin(name_cryptocurrency, getNumberOfCoin(name_cryptocurrency) + number_cryptocurrency);
    // оновили кількість монеток в базі даних + в об'єкті User
    saveTransaction("buy", name_cryptocurrency, number_cryptocurrency, price, total_usd);
    // записали дію в історію транзакцій
    updateBalanceUsd(balance_usd - total_usd);
    // перезаписали в БД + в об'єкті User
}

void User::sellCoin(QString name_cryptocurrency, double number_cryptocurrency, double price, double total_usd)
{
    Database::updateNumberCryptocurrencyMinus(user_name, number_cryptocurrency, name_cryptocurrency);
    updateNumberOfCoin(name_cryptocurrency, getNumberOfCoin(name_cryptocurrency) - number_cryptocurrency);
    // оновили кількість монеток в базі даних + в об'єкті User
    saveTransaction("sell", name_cryptocurrency, number_cryptocurrency, price, total_usd);
    // записали дію в історію транзакцій
    updateBalanceUsd(balance_usd + total_usd);
    // перезаписали в БД + в об'єкті User
}

bool User::HaveEnoughCoins(QString name_coin, double value)
{
    if(getNumberOfCoin(name_coin) >= value)
    {
        return true;
    }
    return false;
}

bool User::HaveEnoughMoney(double value)
{
    if(balance_usd >= value)
    {
        return true;
    }
    return false;
}

double User::getNumberOfCoin(QString name_coin)
{
    for(QPair<QString, double> coin : qAsConst(this->coins_list))
    {
        if(coin.first == name_coin)
        {
            return coin.second;
        }
    }
    return 0.0;
}
