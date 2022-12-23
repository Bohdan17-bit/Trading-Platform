#include "piechartwindow.h"
#include "qdebug.h"
#include "ui_piechartwindow.h"

#include <QtCharts/QLegend>
#include <QtCharts/QPieSeries>
#include <QtCore/QRandomGenerator>
#include "database.h"
#include "singleuser.h"


PiechartWindow::PiechartWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PiechartWindow)
{
    ui->setupUi(this);
    initSettingsChart();
    initSettingsPieSeries();
}

PiechartWindow::~PiechartWindow()
{
    delete ui;
}

void PiechartWindow::showEvent(QShowEvent *event)
{
    //coinSeries->clear();
    //chart->removeSeries(coinSeries);
}

void PiechartWindow::drawDiagram(QVector<QPair<QString, double>> coins)
{
    for(QPair<QString, double> coin : coins)
    {
        if(coin.second != 0)
        {
            *coinSeries << new DrillDownSlice(coin.second, coin.first, coinSeries);

        }
    }
    chart->changeSeries(coinSeries);
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    PiechartWindow::setCentralWidget(chartView);
}


void PiechartWindow::initSettingsChart()
{
    chart = new DrillDownChart();
    chart->setTheme(QChart::ChartThemeLight);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);
}


void PiechartWindow::initSettingsPieSeries()
{
    coinSeries = new QPieSeries();
    coinSeries->setName("Кругова діаграма розподілу портфоліо");
}


void PiechartWindow::getCoins(QVector<QPair<QString, double>> coins)
{
    drawDiagram(coins);
}
