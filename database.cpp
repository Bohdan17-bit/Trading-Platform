#include "database.h"
#include "qvariant.h"
#include <QDebug>
#include "txtreader.h"
#include <QFileInfo>


QSqlDatabase Database::db = QSqlDatabase::addDatabase("QSQLITE");


void Database::initDatabase()
{
    db.setDatabaseName("./db/database.db");
}


void Database::createAllTables()
{
    QSqlQuery query_create_table_User ("CREATE TABLE User"
                         "(name TEXT NOT NULL UNIQUE PRIMARY KEY,"
                         "total_money NUMERIC NOT NULL);");

    QSqlQuery query_create_table_Portfolio ("CREATE TABLE Portfolio"
                              "(name TEXT NOT NULL,"
                              "cryptocurrency TEXT NOT NULL,"
                              "number NUMERIC NOT NULL,"
                              "FOREIGN KEY(name) REFERENCES User(name));");

    QSqlQuery query_create_table_TradeHistory ("CREATE TABLE TradeHistory"
                                 "(name TEXT NOT NULL,"
                                 "action TEXT NOT NULL,"
                                 "cryptocurrency TEXT NOT NULL,"
                                 "number NUMERIC NOT NULL,"
                                 "price NUMERIC NOT NULL,"
                                 "usd NUMERIC NOT NULL,"
                                 "FOREIGN KEY(name) REFERENCES User(name));");

    query_create_table_User.exec();
    query_create_table_Portfolio.exec();
    query_create_table_TradeHistory.exec();
}


void Database::openDatabase()
{
    bool db_file_exist = QFileInfo::exists("./db/database.db");
    db.open();
    if(db_file_exist == false)
    {
        createAllTables();
    }
}


bool Database::userIsExist(QString user_name)
{
    QSqlQuery query;
    query.exec("SELECT * from User");
    qDebug() << "База даних перевіряє, чи існує користувач";
    while(query.next())
    {
        QString temp_name = query.value(0).toString();
        qDebug() << "db:" + temp_name;
        if(user_name == temp_name)
        {
            return true;
        }
    }
    return false;
}


bool Database::accountIsCreated(QString user_name)
{
    QSqlQuery query;
    query.prepare("INSERT INTO User (name, total_money)"
                  "VALUES (:name, :total_money)");
    query.bindValue(":name", user_name);
    query.bindValue(":total_money", 40000);
    return query.exec();
}



bool Database::writeRecordToHistory(QString user_name, QString action, QString name_cryptocurrency, double number_cryptocurrency, double price, double usd)
{
    QSqlQuery query;
    query.prepare("INSERT INTO TradeHistory (name, action, cryptocurrency, number, price, usd)"
                  "VALUES (:name, :action, :cryptocurrency, :number, :price, :usd)");
    query.bindValue(":name", user_name);
    query.bindValue(":action", action);
    query.bindValue(":cryptocurrency", name_cryptocurrency);
    query.bindValue(":number", number_cryptocurrency);
    query.bindValue(":price", price);
    query.bindValue(":usd", usd);
    return query.exec();
}


void Database::createEmptyFieldsPortfolio(QString user_name)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Portfolio (name, cryptocurrency, number) "
               "VALUES (:name, :cryptocurrency, :number)");
    query.bindValue(":name", user_name);
    query.bindValue(":number", 0);
    createFields(query);
}


void Database::createFields(QSqlQuery query)
{
    QStringList list_coins = TXTReader::getListCryptocoins();
    for(int i = 0; i < list_coins.length(); i++)
    {
        query.bindValue(":cryptocurrency", list_coins[i]);
        query.exec();
    }
}


bool Database::rewriteBalance(QString user_name, double balance)
{
    QSqlQuery query;
    query.prepare("UPDATE User SET total_money=? WHERE name=?");
    query.bindValue(0, balance);
    query.bindValue(1, user_name);
    return query.exec();
}


bool Database::updateNumberCryptocurrencyPlus(QString user_name, double number, QString crypto_name)
{
    QSqlQuery query;
    double new_number_crypto = number + getNumberCryptocurrency(user_name, crypto_name);
    query.prepare("UPDATE Portfolio SET number=? WHERE name=? AND cryptocurrency=?");
    query.bindValue(0, new_number_crypto);
    query.bindValue(1, user_name);
    query.bindValue(2, crypto_name);
    return query.exec();
};


bool Database::updateNumberCryptocurrencyMinus(QString user_name, double number, QString crypto_name)
{
    QSqlQuery query;
    double new_number_crypto = getNumberCryptocurrency(user_name, crypto_name) - number;
    query.prepare("UPDATE Portfolio SET number=? WHERE name=? AND cryptocurrency=?");
    query.bindValue(0, new_number_crypto);
    query.bindValue(1, user_name);
    query.bindValue(2, crypto_name);
    return query.exec();
}

double Database::getNumberCryptocurrency(QString user_name, QString crypto_name)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM Portfolio WHERE name =? AND cryptocurrency=?");
    query.bindValue(0, user_name);
    query.bindValue(1, crypto_name);
    query.exec();
    while(query.next())
    {
        return query.value(2).toDouble();
    }
}


QVector<QPair<QString, double>> Database::getNumberAllCryptocurrencies(QString user_name)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM Portfolio WHERE name=?");
    query.bindValue(0, user_name);
    QVector<QPair<QString, double>> coins;
    query.exec();
    while(query.next())
    {
        QPair<QString, double> coin;
        coin.first = query.value(1).toString();
        coin.second = query.value(2).toDouble();
        coins.append(coin);
    }
    return coins;
}


double Database::getBalance(QString user_name)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM User WHERE name =?");
    query.bindValue(0, user_name);
    query.exec();
    while(query.next())
    {
        return query.value(1).toDouble();
    }
}
