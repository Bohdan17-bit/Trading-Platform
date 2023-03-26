#include "window/portfoliowindow.h"
#include "window/ui_portfoliowindow.h"
#include "api/apiaddressbuilder.h"
#include "api/apiservice.h"
#include "utils/txtreader.h"


PortfolioWindow::PortfolioWindow(User *user, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PortfolioWindow)
{
    ui->setupUi(this);
    setWindowTitle("Портфоліо");
    this->user = user;
    initSettingTablePortfolio();
}


PortfolioWindow::~PortfolioWindow()
{
    delete ui;
}


void PortfolioWindow::showEvent(QShowEvent *event)
{
    piechartWindow = new PiechartWindow();
    initDataCryptocoins();
}


void PortfolioWindow::getDataCryptocoinsFromAPI()
{
    QString address = ApiAddressBuilder::getDataAllCryptoPairs();
    QJsonDocument json = ApiService::MakeRequest(address);

    QStringList list_coins = TXTReader::getListCryptocoins();

    QJsonArray arrayJsonCoins = json.array(); // масив об'єктів криптомонет
    list_cryptocoins.clear();
    foreach(const QJsonValue &coin, arrayJsonCoins)
    {
        for(int i = 0; i < list_coins.length(); i++)
        {
            if(coin.toObject().value("symbol") == list_coins[i] + "_USDT")
            {
                 DatabaseCryptocoinsData current_coin;
                 current_coin.price_per_coin = coin.toObject().value("price").toString().toDouble();
                 current_coin.name = coin.toObject().value("symbol").toString();
                 current_coin.daily_change = coin.toObject().value("dailyChange").toString().toDouble() * 100;
                 list_cryptocoins.append(current_coin);
            }
        }
    }
}


void PortfolioWindow::initDataCryptocoins()
{
    getDataCryptocoinsFromAPI();
    getDataCryptocoinsFromDatabase();
    showListCryptocoins();
    initTablePortfolio();
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
    QVector<QPair<QString, double>> coinsDatabase = user->getCoinsList();
    for(int i = 0; i < list_cryptocoins.length(); i++)
    {
        for(int j = 0; j < coinsDatabase.length(); j++)
        {
            if(list_cryptocoins[i].name == coinsDatabase[j].first + "_USDT")
            {
                list_cryptocoins[i].name = coinsDatabase[j].first;
                list_cryptocoins[i].number_coins = coinsDatabase[j].second;
                list_cryptocoins[i].total_cost = coinsDatabase[j].second * list_cryptocoins[i].price_per_coin;
            }
        }
    }
}


void PortfolioWindow::initSettingTablePortfolio()
{
    ui->portfolioTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->portfolioTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->portfolioTableWidget->setColumnCount(4);

    QStringList headers;
    headers << "Назва" << "Кількість" << "В доларах" << "Зміна за день %";
    ui->portfolioTableWidget->setHorizontalHeaderLabels(headers);
}


void PortfolioWindow::initTablePortfolio()
{
    ui->portfolioTableWidget->setRowCount(list_cryptocoins.size());
    QFont font;
    for(int i = 0; i < list_cryptocoins.length(); i++)
    {
        font.setPointSize(10);
        ui->portfolioTableWidget->setItem(i, 0, new QTableWidgetItem(list_cryptocoins[i].name));
        ui->portfolioTableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(list_cryptocoins[i].number_coins)));
        ui->portfolioTableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(list_cryptocoins[i].total_cost)));
        ui->portfolioTableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(list_cryptocoins[i].daily_change)));

        QPixmap pixmap;
        if(list_cryptocoins[i].daily_change >= 0)
        {
            pixmap.load("./images/green_triangle.png");
        }
        else
        {
            pixmap.load("./images/red_triangle.png");
        }
        ui->portfolioTableWidget->item(i, 3)->setIcon(QIcon(pixmap));

        ui->portfolioTableWidget->item(i, 0)->setFont(font);
        ui->portfolioTableWidget->item(i, 1)->setFont(font);
        ui->portfolioTableWidget->item(i, 2)->setFont(font);
        ui->portfolioTableWidget->item(i, 3)->setFont(font);

        ui->portfolioTableWidget->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        ui->portfolioTableWidget->item(i, 1)->setTextAlignment(Qt::AlignCenter);
        ui->portfolioTableWidget->item(i, 2)->setTextAlignment(Qt::AlignCenter);
        ui->portfolioTableWidget->item(i, 3)->setTextAlignment(Qt::AlignCenter);
    }

    for(int i = 0; i < list_cryptocoins.length(); i++)
    {
        if(i % 2 == 0)
        {
            ui->portfolioTableWidget->item(i, 0)->setBackground(QBrush(QColor(216, 225, 246)));
            ui->portfolioTableWidget->item(i, 1)->setBackground(QBrush(QColor(216, 225, 246)));
            ui->portfolioTableWidget->item(i, 2)->setBackground(QBrush(QColor(216, 225, 246)));
            ui->portfolioTableWidget->item(i, 3)->setBackground(QBrush(QColor(216, 225, 246)));
        }
    }
}


void PortfolioWindow::on_tradeWindow_button_clicked()
{
    sound->transitionOnAnotherWindow();
    emit tradeWindowShow();
    this->close();
}


void PortfolioWindow::on_piechartWindow_button_clicked()
{
    sound->transitionOnAnotherWindow();
    connect(this, &PortfolioWindow::sendCoinsData, piechartWindow, &PiechartWindow::getCoins);
    connect(this, &PortfolioWindow::sendSoundObj, piechartWindow, &PiechartWindow::getSoundObj);
    emit sendSoundObj(sound);
    prepare_data_to_pieChart();
    piechartWindow->show();
}


void PortfolioWindow::getSoundObj(Sound *sound)
{
    this->sound = sound;
}


void PortfolioWindow::prepare_data_to_pieChart()
{
    QVector<QPair<QString, double>> coins_to_pieChart;
    double balance = user->discoverBalance();
    QPair<QString, double> balance_usdt;
    balance_usdt.first = "USD";
    balance_usdt.second = balance;
    coins_to_pieChart.append(balance_usdt);
    for(int i = 0; i< list_cryptocoins.length(); i++)
    {
        QPair<QString, double> coin;
        coin.first = list_cryptocoins[i].name;
        coin.second = list_cryptocoins[i].total_cost;
        coins_to_pieChart.append(coin);
    }
    sendCoinsData(coins_to_pieChart);
}
