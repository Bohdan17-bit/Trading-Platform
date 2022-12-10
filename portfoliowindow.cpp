#include "portfoliowindow.h"
#include "ui_portfoliowindow.h"

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
