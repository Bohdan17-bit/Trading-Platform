#ifndef PORTFOLIOWINDOW_H
#define PORTFOLIOWINDOW_H

#include <QWidget>
#include "database.h"
#include "piechartwindow.h"


namespace Ui {
    class PortfolioWindow;
}


struct DatabaseCryptocoinsData
{
    double total_cost = 0;
    double number_coins = 0;
    double daily_change;
    double price_per_coin;
    QString name;

};


class PortfolioWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PortfolioWindow(QWidget *parent = nullptr);
    ~PortfolioWindow();
    QVector <DatabaseCryptocoinsData> list_cryptocoins;
    void getUserName(QString user_name);

signals:
    void tradeWindowShow();

private slots:
    void on_tradeWindow_button_clicked();
    void showListCryptocoins();
    void getDataCryptocoinsFromAPI();
    void getDataCryptocoinsFromDatabase();
    void initDataCryptocoins();

    void initTablePortfolio();
    void initSettingTablePortfolio();

    void on_piechartWindow_button_clicked();

private:
    Ui::PortfolioWindow *ui;
    PiechartWindow *piechartWindow;
    QString user_name;
};

#endif // PORTFOLIOWINDOW_H
