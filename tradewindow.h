#ifndef TRADEWINDOW_H
#define TRADEWINDOW_H

#include <QMainWindow>
#include "timeconverter.h"
#include "apiservice.h"
#include "apiaddressbuilder.h"
#include "candlegraphbuilder.h"
#include "database.h"
#include "portfoliowindow.h"
#include <QGridLayout>
#include <QSqlTableModel>
#include <QMessageBox>

enum Interval { FIVE_MINUTES, FIFTEEN_MINUTES, TWO_HOURS };

QT_BEGIN_NAMESPACE
namespace Ui { class TradeWindow; }
QT_END_NAMESPACE

class TradeWindow : public QMainWindow
{
    Q_OBJECT

public:
    TradeWindow(QWidget *parent = nullptr);
    ~TradeWindow();
    void InitTimers();
    void setDefaultSettings();
    void setCurrentInterval(Interval interval);
    void changeCryptoPair(QString pair);
    void stopAllRequests();
    void startAllRequests();
private:
    Ui::TradeWindow *ui;
    PortfolioWindow *portfolioWindow;
    double last_price = 0;
    QString current_pair;
    QString current_coin;
    QString user_name;
    double balance = 0;
    QTimer *timer_refresh_chart;
    QTimer *timer_refresh_price;
    bool minutes_5_btn;
    Interval interval;
    CandleGraphBuilder *candle_graph;
    QGridLayout *main_layout_diagram;
    QWidget *diagram;
    QSqlTableModel *model;
signals:
    void sendUserName(QString user_name);
public slots:
    void getChartGeneral();
    void getChartData5Minutes();
    void getChartData15Minutes();
    void getChartData2Hours();
    void getPriceCurrentPair();
    void setCurrentPair(QString pair);
    void setPriceToBuyEditTextBox(double base_price);
    void setPriceToSellEditTextBox(double base_price);
    void drawDiagram();
    void parseJson(QJsonDocument document);
private slots:
    void closeEvent(QCloseEvent *event) override;
    void showEvent(QShowEvent *event) override;
    void clearFields();
    void init_table_coins();
    void on_btn_5_minutes_clicked();
    void on_btn_15_minutes_clicked();
    void on_btn_2_hours_clicked();
    void on_table_coins_cellClicked(int row, int column);
    void on_lineEdit_count_buy_textEdited(const QString &arg1);
    void on_lineEdit_count_sell_textEdited(const QString &arg1);
    void update_balance_label();
    void on_btn_buy_cryptocurrency_clicked();
    void on_btn_sell_cryptocurrency_clicked();
    void initTableTradeHistory();
    void refreshTableTradeHistory();
    void on_to_portfolio_btn_clicked();
    void on_exit_button_clicked();
};
#endif // TRADEWINDOW_H
