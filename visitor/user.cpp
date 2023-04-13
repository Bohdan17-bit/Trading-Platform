#include "visitor/user.h"
#include "storage/database.h"
#include <QDebug>
#include "utils/moneyconverter.h"

void User::loadUserData()
{
    balance_usd = Database::getBalance(user_name);
    loadCoinsList();
}

QVector<QPair<QString, double>> User::getCoinsList()
{
    return coins_list;
}

QString User::discoverName()
{
    return user_name;
}

double User::discoverBalance()
{
    return balance_usd;
}

void User::loadCoinsList()
{
    coins_list = Database::getNumberAllCryptocurrencies(user_name);
}

void User::updateBalanceUsd()
{
    balance_usd = Database::getBalance(user_name);
}

void User::setUsername(QString user_name)
{
    this->user_name = user_name;
}

void User::updateNumberOfCoins()
{
    coins_list.clear();
    loadCoinsList();
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

    int total_to_write = MoneyConverter::doubleUsdToInteger(Database::getBalance(user_name)) - MoneyConverter::doubleUsdToInteger(total_usd);
    qDebug() << "HUI : " << total_to_write;
    qDebug() << "HUI : " << MoneyConverter::integerUsdToDouble(total_to_write);
    Database::rewriteBalance(user_name, MoneyConverter::integerUsdToDouble(total_to_write));

    // оновили кількість монеток в базі даних + в об'єкті User
    saveTransaction("buy", name_cryptocurrency, number_cryptocurrency, price, total_usd);
    // записали дію в історію транзакцій
    updateBalanceUsd();
    updateNumberOfCoins();
    // перезаписали в БД + в об'єкті User
}

void User::sellCoin(QString name_cryptocurrency, double number_cryptocurrency, double price, double total_usd)
{
    Database::updateNumberCryptocurrencyMinus(user_name, number_cryptocurrency, name_cryptocurrency);
    int total_to_write = MoneyConverter::doubleUsdToInteger(Database::getBalance(user_name)) + MoneyConverter::doubleUsdToInteger(total_usd);
    Database::rewriteBalance(user_name, MoneyConverter::integerUsdToDouble(total_to_write));
    // оновили кількість монеток в базі даних + в об'єкті User
    saveTransaction("sell", name_cryptocurrency, number_cryptocurrency, price, total_usd);
    // записали дію в історію транзакцій
    updateBalanceUsd();
    updateNumberOfCoins();
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
}
