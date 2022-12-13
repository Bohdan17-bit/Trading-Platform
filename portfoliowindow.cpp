#include "portfoliowindow.h"
#include "ui_portfoliowindow.h"
#include "apiaddressbuilder.h"
#include "apiservice.h"


PortfolioWindow::PortfolioWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PortfolioWindow)
{
    ui->setupUi(this);
    getDataCryptocoins();
}


PortfolioWindow::~PortfolioWindow()
{
    delete ui;
}


void PortfolioWindow::getDataCryptocoins()
{
    QString address = ApiAddressBuilder::getDataAllCryptoPairs();
    QJsonDocument json = ApiService::MakeRequestChartData(address);
}


void PortfolioWindow::on_tradeWindow_button_clicked()
{
    emit tradeWindowShow();
    this->close();
}

