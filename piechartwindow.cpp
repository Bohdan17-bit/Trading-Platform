#include "piechartwindow.h"
#include "ui_piechartwindow.h"

#include <QtCharts/QChartView>
#include <QtCharts/QLegend>
#include <QtCharts/QPieSeries>

PiechartWindow::PiechartWindow(QWidget *parent) :
    QWidget(parent),
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
