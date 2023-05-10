#include "window/piechartwindow.h"
#include "qdebug.h"
#include "ui_piechartwindow.h"

#include <QThread>
#include <QTimer>
#include <QtCharts/QLegend>
#include <QtCharts/QPieSeries>
#include <QtCore/QRandomGenerator>


PiechartWindow::PiechartWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PiechartWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Кругова діаграма"));
    initSettingsChart();
    initSettingsPieSeries();
}

PiechartWindow::~PiechartWindow()
{
    qDebug() <<"destructor PiechartWindow";
    delete ui;
}


void PiechartWindow::closeEvent(QCloseEvent *event)
{
    sound->close();
}


void PiechartWindow::drawDiagram(QVector<QPair<QString, double>> coins)
{
    coinSeries->clear();
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


void PiechartWindow::getSoundObj(Sound *sound)
{
    this->sound = sound;
}

void PiechartWindow::initSettingsPieSeries()
{
    coinSeries = new QPieSeries();
    coinSeries->setName(tr("Кругова діаграма розподілу портфоліо"));
}


void PiechartWindow::getCoins(QVector<QPair<QString, double>> coins)
{
    drawDiagram(coins);
}
