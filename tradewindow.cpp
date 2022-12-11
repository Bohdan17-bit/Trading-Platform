#include "tradewindow.h"
#include "ui_tradewindow.h"
#include <QGridLayout>
#include <cmath>

TradeWindow::TradeWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TradeWindow)
{
    candle_graph = new CandleGraphBuilder();
    main_layout_diagram = new QGridLayout();
    portfolioWindow = new PortfolioWindow();

    ui->setupUi(this);

    setDefaultSettings();
    init_table_coins();
    getPriceCurrentPair();

    connect(timer_refresh_chart, &QTimer::timeout, this, &TradeWindow::getChartGeneral);
    connect(timer_refresh_price, &QTimer::timeout, this, &TradeWindow::getPriceCurrentPair);
    connect(portfolioWindow, &PortfolioWindow::tradeWindowShow, this, &TradeWindow::show);
}


void TradeWindow::initTableTradeHistory()
{
    model = new QSqlTableModel(this);
    model->setTable("TradeHistory");

    model->setFilter("name = '"+ user_name + "'");
    model->select();

    model->setHeaderData(1, Qt::Horizontal, "Дія", Qt::DisplayRole);
    model->setHeaderData(2, Qt::Horizontal, "Монета", Qt::DisplayRole);
    model->setHeaderData(3, Qt::Horizontal, "Число", Qt::DisplayRole);
    model->setHeaderData(4, Qt::Horizontal, "Ціна", Qt::DisplayRole);
    model->setHeaderData(5, Qt::Horizontal, "Долари", Qt::DisplayRole);

    ui->tableView_trade_history->setModel(model);
    ui->tableView_trade_history->setColumnHidden(0, true);
    ui->tableView_trade_history->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}


void TradeWindow::refreshTableTradeHistory()
{
    model->select();
}


void TradeWindow::recieveUserName(QString name)
{
    user_name = name;
    update_balance_label();
    initTableTradeHistory();
}


TradeWindow::~TradeWindow()
{
    delete diagram;
    delete main_layout_diagram;
    delete timer_refresh_chart;
    delete candle_graph;
    delete ui;
}


void TradeWindow::changeCryptoPair(QString coin)
{
    QString pair = "USDT_" + coin;
    setCurrentPair(pair);
}


void TradeWindow::init_table_coins()
{
    ui->table_coins->setColumnCount(10);
    ui->table_coins->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->table_coins->insertRow(0);
    ui->table_coins->setItem(0, 0, new QTableWidgetItem("BTC"));
    ui->table_coins->setItem(0, 1, new QTableWidgetItem("XRP"));
    ui->table_coins->setItem(0, 2, new QTableWidgetItem("ETH"));
    ui->table_coins->setItem(0, 3, new QTableWidgetItem("DASH"));
    ui->table_coins->setItem(0, 4, new QTableWidgetItem("DOGE"));
    ui->table_coins->setItem(0, 5, new QTableWidgetItem("LTC"));
    ui->table_coins->setItem(0, 6, new QTableWidgetItem("BNB"));
    ui->table_coins->setItem(0, 7, new QTableWidgetItem("SOL"));
    ui->table_coins->setItem(0, 8, new QTableWidgetItem("UNI"));
    ui->table_coins->setItem(0, 9, new QTableWidgetItem("TRX"));
    ui->table_coins->setEditTriggers(0); // заборона редагування ячеєк таблиці
    ui->table_coins->horizontalHeader()->hide();
    ui->table_coins->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->table_coins->verticalHeader()->hide();
    for(int i = 0; i < 10; i++)
    {
        ui->table_coins->item(0, i)->setTextAlignment(Qt::AlignCenter);
    }
    ui->table_coins->item(0, 0)->setSelected(true);
    QTableWidgetItem item;
}


void TradeWindow::setDefaultSettings()
{
    Interval temp;
    temp = Interval::FIFTEEN_MINUTES;
    setCurrentInterval(temp);
    setCurrentPair("USDT_BTC");
    InitTimer();
    getChartGeneral();
}


void TradeWindow::update_balance_label()
{
    balance = Database::getBalance(user_name);
    ui->balance_label->setText("Баланс : " + QString::number(balance));
    qDebug() << balance;
}


void TradeWindow::setCurrentInterval(Interval temp)
{
    interval = temp;
}


void TradeWindow::InitTimer()
{
    timer_refresh_chart = new QTimer(this);
    timer_refresh_price = new QTimer(this);

    timer_refresh_chart->start(60000);
    timer_refresh_price->start(10000);
}


void TradeWindow::setCurrentPair(QString pair)
{
    current_pair = pair;
}


void TradeWindow::getPriceCurrentPair()
{
    QString address = ApiAddressBuilder::getTicker();
    QJsonDocument document = ApiService::MakeRequestChartData(address);
    QJsonObject object = document.object();
    QJsonObject nest = object[current_pair].toObject();
    if(nest["last"].toString().toDouble() > last_price)
    {
        ui->price_label->setStyleSheet("color: green;");
    }
    else
    {
        ui->price_label->setStyleSheet("color: red;");
    }
    last_price = nest["last"].toString().toDouble();
    last_price = round(last_price*100)/100;
    ui->price_label->setText("Ціна : " + QString::number(last_price) + "$");
    setPriceToBuyEditTextBox(last_price);
    setPriceToSellEditTextBox(last_price);
}


void TradeWindow::setPriceToBuyEditTextBox(double base_price)
{
    double final_price = base_price * 1.002;
    if(ui->lineEdit_count_buy->text().isEmpty() == false)
    {
        double number = ui->lineEdit_count_buy->text().toDouble();
        ui->lineEdit_total_to_buy->setText(QString::number(final_price * number));
    }
    ui->linedEdit_price_buy->setText(QString::number(final_price));
}


void TradeWindow::setPriceToSellEditTextBox(double base_price)
{
    double final_price = base_price * 0.998;
    if(ui->lineEdit_count_sell->text().isEmpty() == false)
    {
        double number = ui->lineEdit_count_sell->text().toDouble();
        ui->lineEdit_total_to_sell->setText(QString::number(final_price * number));
    }
    ui->linedEdit_price_sell->setText(QString::number(final_price));
}


void TradeWindow::clearFields()
{
    ui->lineEdit_total_to_buy->clear();
    ui->lineEdit_total_to_sell->clear();
    ui->lineEdit_count_sell->clear();
    ui->lineEdit_count_buy->clear();
}


void TradeWindow::on_lineEdit_count_buy_textEdited(const QString &arg1)
{
    if(ui->lineEdit_count_buy->text().isEmpty())
    {
        ui->lineEdit_total_to_buy->clear();
    }
    else
    {
        double price = ui->linedEdit_price_buy->text().toDouble();
        double number = ui->lineEdit_count_buy->text().toDouble();
        double total = price * number;
        ui->lineEdit_total_to_buy->setText(QString::number(total));
    }
}


void TradeWindow::on_lineEdit_count_sell_textEdited(const QString &arg1)
{
    if(ui->lineEdit_count_sell->text().isEmpty())
    {
        ui->lineEdit_total_to_sell->clear();
    }
    else
    {
        double price = ui->linedEdit_price_sell->text().toDouble();
        double number = ui->lineEdit_count_sell->text().toDouble();
        double total = price * number;
        ui->lineEdit_total_to_sell->setText(QString::number(total));
    }
}


void TradeWindow::getChartGeneral()
{
    switch(interval)
    {
    case FIVE_MINUTES:
        getChartData5Minutes();
        break;
    case FIFTEEN_MINUTES:
        getChartData15Minutes();
        break;
    case TWO_HOURS:
        getChartData2Hours();
        break;
    }
}


void TradeWindow::getChartData5Minutes()
{
    QString api_address
            = ApiAddressBuilder::getChartData(current_pair, TimeConverter::getOneAndHalfHourUnixTime(),
                                                    TimeConverter::getCurrentUnixTime(),
                                                    TimeConverter::get5MinuteInSeconds());
    QJsonDocument json = ApiService::MakeRequestChartData(api_address);
    qDebug() << api_address;
    parseJson(json);
}


void TradeWindow::getChartData15Minutes()
{
    QString api_address = ApiAddressBuilder::getChartData(current_pair,
                                                          TimeConverter::getFourHoursUnixTime(),
                                                          TimeConverter::getCurrentUnixTime(),
                                                          TimeConverter::get15MinuteInSeconds());
    QJsonDocument json = ApiService::MakeRequestChartData(api_address);
    qDebug() << api_address;
    parseJson(json);
}


void TradeWindow::getChartData2Hours()
{
    QString api_address = ApiAddressBuilder::getChartData(current_pair,
                                                          TimeConverter::getLastOneDayUnixTime(),
                                                          TimeConverter::getCurrentUnixTime(),
                                                          TimeConverter::get2HourInSeconds());
    QJsonDocument json = ApiService::MakeRequestChartData(api_address);
    qDebug() << api_address;
    parseJson(json);
}


void TradeWindow::parseJson(QJsonDocument document)
{
    candle_graph->refresh_graph_builder();
    QJsonArray jsonArray = document.array();
    foreach(const QJsonValue &value, jsonArray)
    {
        qreal date = value.toObject().value("date").toString().toDouble();
        qreal high = value.toObject().value("high").toString().toDouble();
        qreal low = value.toObject().value("low").toString().toDouble();
        qreal open = value.toObject().value("open").toString().toDouble();
        qreal close = value.toObject().value("close").toString().toDouble();
        candle_graph->addCandleStickSet(date, open, close, low, high);
    }
    drawDiagram();
}


void TradeWindow::drawDiagram()
{
    if(diagram != nullptr)
    {
        main_layout_diagram->removeWidget(diagram);
    }
    diagram = candle_graph->getGraphChart();
    main_layout_diagram->addWidget(diagram);
    ui->widget->setLayout(main_layout_diagram);
}


void TradeWindow::on_btn_5_minutes_clicked()
{
    setCurrentInterval(Interval::FIVE_MINUTES);
    ui->btn_5_minutes->setStyleSheet("border: 2px solid green;	background: greenyellow; height: 40px; width: 40px; border-radius: 5px;");
    ui->btn_2_hours->setStyleSheet("background:#92E2F1; border: 2px solid #158094; height: 40px; width: 40px; border-radius: 5px;");
    ui->btn_15_minutes->setStyleSheet("background:#92E2F1; border: 2px solid #158094; height: 40px; width: 40px; border-radius: 5px;");
    getChartGeneral();
}


void TradeWindow::on_btn_15_minutes_clicked()
{
    setCurrentInterval(Interval::FIFTEEN_MINUTES);
    ui->btn_15_minutes->setStyleSheet("border: 2px solid green; background: greenyellow; height: 40px; width: 40px; border-radius: 5px;");
    ui->btn_2_hours->setStyleSheet("background:#92E2F1; border: 2px solid #158094; height: 40px; width: 40px; border-radius: 5px;");
    ui->btn_5_minutes->setStyleSheet("background:#92E2F1; border: 2px solid #158094; height: 40px; width: 40px; border-radius: 5px;");
    getChartGeneral();
}


void TradeWindow::on_btn_2_hours_clicked()
{
    setCurrentInterval(Interval::TWO_HOURS);
    ui->btn_2_hours->setStyleSheet("border: 2px solid green; background: greenyellow; height: 40px; width: 40px; border-radius: 5px;");
    ui->btn_15_minutes->setStyleSheet("background:#92E2F1; border: 2px solid #158094; height: 40px; width: 40px; border-radius: 5px;");
    ui->btn_5_minutes->setStyleSheet("background:#92E2F1; border: 2px solid #158094; height: 40px; width: 40px; border-radius: 5px;");
    getChartGeneral();
}


void TradeWindow::on_table_coins_cellClicked(int row, int column)
{
    changeCryptoPair(ui->table_coins->item(row, column)->text());
    clearFields();
    getPriceCurrentPair();
    getChartGeneral();
}


void TradeWindow::on_btn_buy_cryptocurrency_clicked()
{
    double total = ui->lineEdit_total_to_buy->text().toDouble();
    double number_crypto = ui->lineEdit_count_buy->text().toDouble();
    if(balance >= total)
    {
        balance = balance - total;
        Database::rewriteBalance(user_name, balance);
        update_balance_label();
        int current_column = ui->table_coins->currentColumn();
        if(current_column < 0)
        {
            current_column = 0;
        }
        QString cryptocurrency = ui->table_coins->item(0, current_column)->text();
        Database::updateNumberCryptocurrencyPlus(user_name, number_crypto, cryptocurrency);
        double price = ui->linedEdit_price_buy->text().toDouble();
        total = round(total*100)/100;
        Database::writeRecordToHistory(user_name, "buy", cryptocurrency, number_crypto, price, total);
        refreshTableTradeHistory();
    }
    else
    {
        QMessageBox message;
        message.setText("У вас недостатньо коштів!");
        message.exec();
    }
}


void TradeWindow::on_btn_sell_cryptocurrency_clicked()
{
    int current_column = ui->table_coins->currentColumn();
    if(current_column < 0)
    {
        current_column = 0;
    }
    QString cryptocurrency = ui->table_coins->item(0, current_column)->text();
    double old_number_cryptocurrency = Database::getNumberCryptocurrency(user_name, cryptocurrency);
    double count_cryptocurrency_to_sell = ui->lineEdit_count_sell->text().toDouble();
    if(old_number_cryptocurrency >= count_cryptocurrency_to_sell)
    {
        double total_usd_to_get = ui->lineEdit_total_to_sell->text().toDouble();
        double price = ui->linedEdit_price_sell->text().toDouble();
        balance += total_usd_to_get;
        Database::rewriteBalance(user_name, balance);
        update_balance_label();
        Database::updateNumberCryptocurrencyMinus(user_name, count_cryptocurrency_to_sell, cryptocurrency);
        total_usd_to_get = round(total_usd_to_get*100)/100;
        Database::writeRecordToHistory(user_name, "sell", cryptocurrency, count_cryptocurrency_to_sell, price, total_usd_to_get);
        refreshTableTradeHistory();
    }
    else
    {
        QMessageBox message;
        message.setText("У вас недостатньо криптовалюти!");
        message.exec();
    }
}


void TradeWindow::on_to_portfolio_btn_clicked()
{
    portfolioWindow->show();
    this->close();
}


void TradeWindow::on_exit_button_clicked()
{
    qApp->quit();
}

