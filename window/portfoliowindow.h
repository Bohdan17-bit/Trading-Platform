#ifndef PORTFOLIOWINDOW_H
#define PORTFOLIOWINDOW_H

#include <QWidget>
#include "window/piechartwindow.h"
#include "visitor/user.h"
#include "utils/sound.h"

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
    explicit PortfolioWindow(User *user, QWidget *parent = nullptr);
    ~PortfolioWindow();
    QVector <DatabaseCryptocoinsData> list_cryptocoins;
    void getDataCryptocoinsFromAPI();
    void getSoundObj(Sound *sound);
    void changeEvent(QEvent *event) override;

signals:
    void tradeWindowShow();
    void sendSoundObj(Sound *sound);

private slots:
    void on_tradeWindow_button_clicked();
    void showListCryptocoins();
    void getDataCryptocoinsFromDatabase();
    void initDataCryptocoins();

    void initTablePortfolio();
    void initSettingTablePortfolio();

    void on_piechartWindow_button_clicked();
    void prepare_data_to_pieChart();
    void showEvent(QShowEvent *event) override;

signals:
    void sendCoinsData(QVector<QPair<QString, double>> coins);

private:
    Ui::PortfolioWindow *ui;
    PiechartWindow *piechartWindow;
    User *user;
    Sound *sound;
};

#endif // PORTFOLIOWINDOW_H
