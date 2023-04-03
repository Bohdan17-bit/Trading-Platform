#ifndef TRADEWINDOW_H
#define TRADEWINDOW_H

#include "utils/timeconverter.h"
#include "api/apiservice.h"
#include "api/apiaddressbuilder.h"
#include "candles/candlegraphbuilder.h"
#include "window/portfoliowindow.h"
#include "tablemodel/tablemodeltradehistory.h"
#include "api/apiserviceresponse.h"

#include <QMainWindow>
#include <QGridLayout>
#include <QSqlTableModel>
#include <QMessageBox>
#include "visitor/user.h"
#include "utils/sound.h"

enum Interval { FIVE_MINUTES, FIFTEEN_MINUTES, TWO_HOURS };

QT_BEGIN_NAMESPACE
namespace Ui { class TradeWindow; }
QT_END_NAMESPACE

class TradeWindow : public QMainWindow
{
    Q_OBJECT

public:
    TradeWindow(User *user, QWidget *parent = nullptr);
    ~TradeWindow();
    void InitTimers();
    void setDefaultSettings();
    void setCurrentInterval(Interval interval);
    void changeCryptoPair(QString pair);
    void stopAllRequests();
    void startAllRequests();
    void getSoundObj(Sound *sound);
private:
    Ui::TradeWindow *ui;
    PortfolioWindow *portfolioWindow;
    QLabel *label_process;
    bool no_internet_connection;
    double last_price = 0;
    QString current_pair;
    QString current_coin;
    User *user;
    Sound *sound;
    QTimer *timer_refresh_chart;
    QTimer *timer_refresh_price;
    bool minutes_5_btn;
    Interval interval;
    CandleGraphBuilder *candle_graph;
    QBoxLayout *main_layout_diagram;
    QWidget *diagram;
    QMovie *movie_loading;
    QJsonArray last_candle;
    TableModelTradeHistory *model;
signals:
    void sendSoundObj(Sound *sound);
public slots:
    void getChartGeneral();
    void getChartData5Minutes();
    void getChartData15Minutes();
    void getChartData2Hours();
    void getLastCandle();
    void setLastCandle(QJsonDocument document);
    void getPriceCurrentPair();
    void setCurrentPair(QString pair);
    void setPriceToBuyEditTextBox(double base_price);
    void setPriceToSellEditTextBox(double base_price);
    void drawDiagram();
    void reDrawCandleChart(ApiServiceResponse response);
private slots:
    void closeEvent(QCloseEvent *event) override;
    void showEvent(QShowEvent *event) override;
    void resizeEvent(QResizeEvent *e) override;
    void closeApp();
    void update_visible_columns_candleChart();
    void clearFields();
    void init_table_coins();
    void on_btn_5_minutes_clicked();
    void on_btn_15_minutes_clicked();
    void on_btn_2_hours_clicked();
    void on_table_coins_cellClicked(int row, int column);
    void on_lineEdit_count_buy_textEdited(const QString &arg1);
    void on_lineEdit_count_sell_textEdited(const QString &arg1);
    void update_balance_label();
    void update_coins_balance_label();
    void on_btn_buy_cryptocurrency_clicked();
    void on_btn_sell_cryptocurrency_clicked();
    void initTableTradeHistory();
    void refreshTableTradeHistory();
    void on_to_portfolio_btn_clicked();
    void on_exit_button_clicked();
    void update_gui_after_transaction();
    void setLoadingInsteadDiagram();
    void setDiragramInsteadLoading();
    void initLoading();
    void disabledBuySellAction();
    void enableBuySellAction();
    void on_table_coins_cellEntered(int row, int column);
};
#endif // TRADEWINDOW_H
