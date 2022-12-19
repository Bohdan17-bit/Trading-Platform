#include "portfoliowindow.h"
#include "ui_portfoliowindow.h"
#include "apiaddressbuilder.h"
#include "apiservice.h"
#include "txtreader.h"

PortfolioWindow::PortfolioWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PortfolioWindow)
{
    ui->setupUi(this);
}


PortfolioWindow::~PortfolioWindow()
{
    delete ui;
}


void PortfolioWindow::getDataCryptocoinsFromAPI()
{
    QString address = ApiAddressBuilder::getDataAllCryptoPairs();
    QJsonDocument json = ApiService::MakeRequest(address);

    QStringList list_coins = TXTReader::getListCryptocoins();

    QJsonArray arrayJsonCoins = json.array(); // масив об'єктів криптомонет
    foreach(const QJsonValue &coin, arrayJsonCoins)
    {
        for(int i = 0; i < list_coins.length(); i++)
        {
            if(coin.toObject().value("symbol") == list_coins[i] + "_USDT")
            {
                 DatabaseCryptocoinsData current_coin;
                 current_coin.price_per_coin = coin.toObject().value("price").toString().toDouble();
                 current_coin.name = coin.toObject().value("symbol").toString();
                 current_coin.daily_change = coin.toObject().value("dailyChange").toString().toDouble();
                 list_cryptocoins.append(current_coin);
            }
        }
    }

}


void PortfolioWindow::getUserName(QString user_name)
{
    this->user_name = user_name;
    qDebug() << "PortfolioWindow: " << user_name;
    initDataCryptocoins();
}


void PortfolioWindow::initDataCryptocoins()
{
    getDataCryptocoinsFromAPI();
    getDataCryptocoinsFromDatabase();
    showListCryptocoins();
}


void PortfolioWindow::showListCryptocoins()
{
    foreach(const DatabaseCryptocoinsData coin, list_cryptocoins)
    {
        qDebug() << "Name of coin: " << coin.name;
        qDebug() << "Price per coin: " << coin.price_per_coin;
        qDebug() << "Number this coins: " << coin.number_coins;
        qDebug() << "Daily change: " << coin.daily_change;
        qDebug() << "Total cost: " << coin.total_cost;
    }
}


void PortfolioWindow::getDataCryptocoinsFromDatabase()
{
    QVector<QPair<QString, double>> coinsDatabase = Database::getNumberAllCryptocurrencies(user_name);
    for(int i = 0; i < list_cryptocoins.length(); i++)
    {
        for(int j = 0; j < coinsDatabase.length(); j++)
        {
            if(list_cryptocoins[i].name == coinsDatabase[j].first + "_USDT")
            {
                list_cryptocoins[i].number_coins = coinsDatabase[i].second;
                list_cryptocoins[i].total_cost = coinsDatabase[i].second * list_cryptocoins[i].price_per_coin;
            }
        }
    }
}


void PortfolioWindow::on_tradeWindow_button_clicked()
{
    emit tradeWindowShow();
    this->close();
}

