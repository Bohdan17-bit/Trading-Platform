#include "window/tradewindow.h"
#include "window/ui_tradewindow.h"
#include "txtreader.h"
#include "candles/candlesticklistbuilder.h"
#include <QSslSocket>

#include <QGridLayout>
#include "api/apiserviceresponse.h"

TradeWindow::TradeWindow(User *user, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TradeWindow)
{
    ui->setupUi(this);
    this->user = user;
    setWindowTitle("Головне вікно");
    no_internet_connection = false;

    candle_graph = new CandleGraphBuilder();
    main_layout_diagram = new QBoxLayout(QBoxLayout::RightToLeft);

    initLoading();

    portfolioWindow = new PortfolioWindow(user);

    diagram = candle_graph->getGraphChartView();

    main_layout_diagram->addWidget(diagram);
    main_layout_diagram->addWidget(label_process, Qt::AlignCenter);
    label_process->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    ui->widget->setLayout(main_layout_diagram);

    setDefaultSettings();
    getChartGeneral();
    init_table_coins();
    initTableTradeHistory();
    update_balance_label();
    update_coins_balance_label();
    getPriceCurrentPair();


    connect(timer_refresh_chart, &QTimer::timeout, this, &TradeWindow::getLastCandle);
    connect(timer_refresh_price, &QTimer::timeout, this, &TradeWindow::getPriceCurrentPair);
    connect(portfolioWindow, &PortfolioWindow::tradeWindowShow, this, &TradeWindow::show);

    connect(candle_graph->getGraphChartView(), &ChartView::mousePress, this, &TradeWindow::stopAllRequests);
    connect(candle_graph->getGraphChartView(), &ChartView::mouseRelease, this, &TradeWindow::startAllRequests);
    update_visible_columns_candleChart();

}


void TradeWindow::showEvent(QShowEvent *event)
{
    startAllRequests();
}


void TradeWindow::closeEvent(QCloseEvent *event)
{
    stopAllRequests();
}


void TradeWindow::stopAllRequests()
{
    timer_refresh_chart->stop();
    timer_refresh_price->stop();
    qDebug() << "Зупинка усіх запитів!";
}


void TradeWindow::startAllRequests()
{
    timer_refresh_price->start(1000);
    timer_refresh_chart->start(10000); // перевірка оновлення графіку кожні 10 секунд
}


void TradeWindow::initTableTradeHistory()
{
    model = new TableModelTradeHistory(this);
    model->setTable("TradeHistory");

    model->setFilter("name = '"+ user->discoverName() + "'");
    model->select();

    //model->setHeaderData(1, Qt::Horizontal, "Дія", Qt::DisplayRole);
    model->setHeaderData(2, Qt::Horizontal, "Монета", Qt::DisplayRole);
    model->setHeaderData(3, Qt::Horizontal, "Число", Qt::DisplayRole);
    model->setHeaderData(4, Qt::Horizontal, "Ціна", Qt::DisplayRole);
    model->setHeaderData(5, Qt::Horizontal, "Долари", Qt::DisplayRole);


    ui->tableView_trade_history->setModel(model);
    ui->tableView_trade_history->setColumnHidden(0, true);
    ui->tableView_trade_history->setColumnHidden(1, true);
    ui->tableView_trade_history->verticalHeader()->setVisible(false);
    ui->tableView_trade_history->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}


void TradeWindow::refreshTableTradeHistory()
{
    model->select();
}


TradeWindow::~TradeWindow()
{
    delete diagram;
    delete main_layout_diagram;
    delete candle_graph;
    delete ui;
}


void TradeWindow::getSoundObj(Sound *sound)
{
    this->sound = sound;
}


void TradeWindow::changeCryptoPair(QString coin)
{
    QString pair = coin + "_USDT";
    current_coin = coin;
    setCurrentPair(pair);
}


void TradeWindow::init_table_coins()
{
    QStringList list_coins = TXTReader::getListCryptocoins();
    int number_coins = list_coins.length();
    ui->table_coins->setColumnCount(number_coins);

    ui->table_coins->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->table_coins->insertRow(0);
    for(int i = 0; i < list_coins.length(); i++)
    {
        ui->table_coins->setItem(0, i, new QTableWidgetItem(list_coins.at(i)));
    }

    ui->table_coins->setEditTriggers(0); // заборона редагування ячеєк таблиці
    ui->table_coins->horizontalHeader()->hide();
    ui->table_coins->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->table_coins->verticalHeader()->hide();
    for(int i = 0; i < number_coins; i++)
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
    setCurrentPair("BTC_USDT");
    current_coin = "BTC";
    InitTimers();
    getChartGeneral();
}


void TradeWindow::update_balance_label()
{
    ui->balance_label->setText("Баланс : " + QString::number(user->discoverBalance()));
}


void TradeWindow::update_coins_balance_label()
{
    int current_column = ui->table_coins->currentColumn();
    if(current_column < 0)
    {
        current_column = 0;
    }
    QString cryptocurrency = ui->table_coins->item(0, current_column)->text();
    ui->coins_balance_label->setText("Монети: " + QString::number(user->getNumberOfCoin(cryptocurrency)));
}


void TradeWindow::setCurrentInterval(Interval temp)
{
    interval = temp;
}


void TradeWindow::InitTimers()
{
    timer_refresh_chart = new QTimer(this);
    timer_refresh_price = new QTimer(this);
    startAllRequests();
}


void TradeWindow::setCurrentPair(QString pair)
{
    current_pair = pair;
}


void TradeWindow::getPriceCurrentPair()
{
    QString address = ApiAddressBuilder::getPriceCryptoPair(current_pair);
    QJsonDocument document = ApiService::MakeRequest(address);
    QJsonObject object = document.object();
    QString price = object["markPrice"].toString();
    if(price.toDouble() > last_price)
    {
        ui->price_label->setStyleSheet("color: green;");
    }
    else
    {
        ui->price_label->setStyleSheet("color: red;");
    }
    last_price = price.toDouble();
    ui->price_label->setText("Ціна : " + QString::number(last_price) + "$");
    if(last_price == 0)
    {
        if(no_internet_connection == false)
        {
            no_internet_connection = true;
            disabledBuySellAction();
            setLoadingInsteadDiagram();
            return;
        }
    }
    else
    {
        if(no_internet_connection == true)
        {
            getChartGeneral();
            no_internet_connection = false;
            enableBuySellAction();
        }
    }
    setPriceToBuyEditTextBox(last_price);
    setPriceToSellEditTextBox(last_price);
}


void TradeWindow::enableBuySellAction()
{
    ui->lineEdit_count_buy->setDisabled(false);
    ui->lineEdit_count_sell->setDisabled(false);
    ui->btn_buy_cryptocurrency->setDisabled(false);
    ui->btn_sell_cryptocurrency->setDisabled(false);
}


void TradeWindow::disabledBuySellAction()
{
    ui->lineEdit_count_buy->setDisabled(true);
    ui->lineEdit_count_sell->setDisabled(true);
    ui->btn_buy_cryptocurrency->setDisabled(true);
    ui->btn_sell_cryptocurrency->setDisabled(true);
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


void TradeWindow::initLoading()
{
    movie_loading = new QMovie("./images/loading.gif");
    movie_loading->setScaledSize(QSize(150, 150));
    label_process = new QLabel();
    label_process->setAlignment(Qt::AlignCenter);
    label_process->setMovie(movie_loading);
    movie_loading->start();
}


void TradeWindow::setDiragramInsteadLoading()
{
    label_process->hide();
    diagram->show();
}


void TradeWindow::setLoadingInsteadDiagram()
{
    diagram->hide();
    label_process->show();
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
    QString api_address;
    api_address
        = ApiAddressBuilder::getChartData("USDT_" + current_coin,
                                                TimeConverter::getLastQuarterUnixTime(),
                                                TimeConverter::getCurrentUnixTime(),
                                                TimeConverter::get5MinuteInSeconds());

    ApiServiceResponse response(ApiService::MakeRequest(api_address));    // об'єкт сервісу
    qDebug() << api_address;
    reDrawCandleChart(response);
}


void TradeWindow::getChartData15Minutes()
{
    QString api_address;
    api_address = ApiAddressBuilder::getChartData("USDT_" + current_coin,
                                                      TimeConverter::getLastOneDayUnixTime(),
                                                      TimeConverter::getCurrentUnixTime(),
                                                      TimeConverter::get15MinuteInSeconds());
    ApiServiceResponse response(ApiService::MakeRequest(api_address));    // об'єкт сервісу
    qDebug() << api_address;
    reDrawCandleChart(response);
}


void TradeWindow::getChartData2Hours()
{
    QString api_address;
    api_address = ApiAddressBuilder::getChartData("USDT_" + current_coin,
                                                      TimeConverter::getLastWeekUnixTime(),
                                                      TimeConverter::getCurrentUnixTime(),
                                                      TimeConverter::get2HourInSeconds());
    ApiServiceResponse response(ApiService::MakeRequest(api_address));    // об'єкт сервісу
    qDebug() << api_address;
    reDrawCandleChart(response);
}


void TradeWindow::getLastCandle()
{
    QString api_address;
    switch(interval)
    {
    case FIVE_MINUTES:
        api_address = ApiAddressBuilder::getChartData("USDT_" + current_coin,
                                                          TimeConverter::getLast5MinuteInSeconds(),
                                                          TimeConverter::getCurrentUnixTime(),
                                                          TimeConverter::get5MinuteInSeconds());
        break;
    case FIFTEEN_MINUTES:
        api_address = ApiAddressBuilder::getChartData("USDT_" + current_coin,
                                                          TimeConverter::getLast15MinuteInSeconds(),
                                                          TimeConverter::getCurrentUnixTime(),
                                                          TimeConverter::get15MinuteInSeconds());
        break;
    case TWO_HOURS:
        api_address = ApiAddressBuilder::getChartData("USDT_" + current_coin,
                                                          TimeConverter::getLast2HourInSeconds(),
                                                          TimeConverter::getCurrentUnixTime(),
                                                          TimeConverter::get2HourInSeconds());
        break;
    }
    qDebug() << api_address;
    ApiServiceResponse response(ApiService::MakeRequest(api_address));
    if(response.get_response().isArray() == false)
    {
        setLoadingInsteadDiagram();
        return;
    }
    setDiragramInsteadLoading();
    setLastCandle(response.get_response());
}


void TradeWindow::setLastCandle(QJsonDocument document)
{
    QJsonArray jsonArray = document.array();
    QJsonValue new_last_candle = jsonArray.last();

    QString date = new_last_candle.toObject().value("date").toString();

    if(date != last_candle.toObject().value("date").toString())
    {
        getChartGeneral();
    }
}


void TradeWindow::reDrawCandleChart(ApiServiceResponse response)
{
    if(response.get_response().isArray() == false)
    {
        setLoadingInsteadDiagram();
        return;
    }
    setDiragramInsteadLoading();
    candle_graph->refresh_graph_builder();
    // перестворюємо діаграму
    candle_graph->CandleStickList = (CandleStickList*) new CandleStickListBuilder(response);
    // створення адаптеру
    candle_graph->addAllCandleStickSets(candle_graph->CandleStickList->get_list_candlestick());
    // клієнт викликає адаптер і складає свічки
    last_candle = response.get_response().array().last();
    // запам'ятовуємо останню свічку для перевірок
    drawDiagram();
    // перемальовуємо діаграму
}


void TradeWindow::drawDiagram()
{
    candle_graph->createNewChart();
    update_visible_columns_candleChart();
}


void TradeWindow::update_visible_columns_candleChart()
{
    qDebug() << candle_graph->getGraphChartView()->chart()->size().width();
    candle_graph->setLimitPoints(candle_graph->getGraphChartView()->chart()->size().width() / 100); // 100 px для кожної колонки
}


void TradeWindow::resizeEvent(QResizeEvent *e)
{
    update_visible_columns_candleChart();
}


void TradeWindow::on_btn_5_minutes_clicked()
{
    sound->simpleClick();
    setCurrentInterval(Interval::FIVE_MINUTES);
    ui->btn_5_minutes->setStyleSheet("border: 2px solid green;	background: greenyellow; height: 40px; width: 40px; border-radius: 5px;");
    ui->btn_2_hours->setStyleSheet("background:#92E2F1; border: 2px solid #158094; height: 40px; width: 40px; border-radius: 5px;");
    ui->btn_15_minutes->setStyleSheet("background:#92E2F1; border: 2px solid #158094; height: 40px; width: 40px; border-radius: 5px;");
    getChartGeneral();
}


void TradeWindow::on_btn_15_minutes_clicked()
{
    sound->simpleClick();
    setCurrentInterval(Interval::FIFTEEN_MINUTES);
    ui->btn_15_minutes->setStyleSheet("border: 2px solid green; background: greenyellow; height: 40px; width: 40px; border-radius: 5px;");
    ui->btn_2_hours->setStyleSheet("background:#92E2F1; border: 2px solid #158094; height: 40px; width: 40px; border-radius: 5px;");
    ui->btn_5_minutes->setStyleSheet("background:#92E2F1; border: 2px solid #158094; height: 40px; width: 40px; border-radius: 5px;");
    getChartGeneral();
}


void TradeWindow::on_btn_2_hours_clicked()
{
    sound->simpleClick();
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
    update_coins_balance_label();
}


void TradeWindow::update_gui_after_transaction()
{
    refreshTableTradeHistory();
    update_coins_balance_label();
    update_balance_label();
}


void TradeWindow::on_btn_buy_cryptocurrency_clicked()
{
    double total_usd_spend = ui->lineEdit_total_to_buy->text().toDouble();
    double number_crypto = ui->lineEdit_count_buy->text().toDouble();
    double price = ui->linedEdit_price_buy->text().toDouble();

    if(ui->lineEdit_count_buy->text() == "0" || ui->lineEdit_count_buy->text() == "")
    {
        sound->error();
        QMessageBox message;
        message.setText("Введіть число криптовалюти!");
        message.exec();
        return;
    }

    int current_column = ui->table_coins->currentColumn();
    if(current_column < 0)
    {
        current_column = 0;
    }

    QString cryptocurrency = ui->table_coins->item(0, current_column)->text();

    if(user->HaveEnoughMoney(total_usd_spend))
    {
        sound->processComplete();
        user->buyCoin(cryptocurrency, number_crypto, price, total_usd_spend);
        update_gui_after_transaction();
    }
    else
    {
        sound->error();
        QMessageBox message;
        message.setText("У вас недостатньо коштів!");
        message.exec();
    }
}


void TradeWindow::on_btn_sell_cryptocurrency_clicked()
{
    if(ui->lineEdit_count_sell->text() == "0" || ui->lineEdit_count_sell->text() == "")
    {
        sound->error();
        QMessageBox message;
        message.setText("Введіть число криптовалюти!");
        message.exec();
        return;
    }

    double count_usd_to_get = ui->lineEdit_total_to_sell->text().toDouble();
    double price = ui->linedEdit_price_sell->text().toDouble();
    double count_cryptocurrency_to_sell = ui->lineEdit_count_sell->text().toDouble();

    int current_column = ui->table_coins->currentColumn();
    if(current_column < 0)
    {
        current_column = 0;
    }

    QString cryptocurrency = ui->table_coins->item(0, current_column)->text();

    if(user->HaveEnoughCoins(cryptocurrency, count_cryptocurrency_to_sell))
    {
        sound->processComplete();
        user->sellCoin(cryptocurrency, count_cryptocurrency_to_sell, price, count_usd_to_get);
        update_gui_after_transaction();
    }
    else
    {
        sound->error();
        QMessageBox message;
        message.setText("У вас недостатньо криптовалюти!");
        message.exec();
    }
}


void TradeWindow::on_to_portfolio_btn_clicked()
{
    if(no_internet_connection)
    {
        sound->error();
        QMessageBox message;
        message.setText("Неможливо переглянути портфель!\nВідсутнє підключення до мережі Інтернет!");
        sound->error();
        message.exec();
    }
    else
    {
        sound->transitionOnAnotherWindow();
        connect(this, &TradeWindow::sendSoundObj, portfolioWindow, &PortfolioWindow::getSoundObj);
        emit sendSoundObj(sound);
        portfolioWindow->show();
        this->close();
    }
}


void TradeWindow::on_exit_button_clicked()
{
    sound->close();
    QTimer::singleShot(1000, this, SLOT(closeApp()));
}

void TradeWindow::closeApp()
{
    qApp->exit();
}

void TradeWindow::on_table_coins_cellEntered(int row, int column)
{
    sound->hover();
}

