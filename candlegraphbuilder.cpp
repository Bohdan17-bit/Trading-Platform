#include "candlegraphbuilder.h"
#include <QDebug>


CandleGraphBuilder::CandleGraphBuilder()
{
    chart = nullptr;
    oldChart = nullptr;
    CandleStickList = nullptr; // adapter
    chartView = new ChartView();
    chartView->setRenderHint(QPainter::Antialiasing);
    initAcmeSeries();
}


void CandleGraphBuilder::initChartSettings()
{
    //chart->setAnimationOptions(QtCharts::QChart::AnimationOption::SeriesAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
}


void CandleGraphBuilder::setLimitPoints(int number_points)
{
    if(categories.isEmpty())
        return;
    int id_time_last_element = categories.size() - 1;
    qDebug() << categories.at(id_time_last_element - number_points + 1) << " and " << categories.at(id_time_last_element);
    axisTime->setRange(categories.at(id_time_last_element - number_points + 1), categories.at(id_time_last_element));
}


void CandleGraphBuilder::createNewChart()
{
    oldChart = chart;

    chart = new QtCharts::QChart();

    chart->addSeries(acmeSeries);

    initChartSettings();

    initAxes();

    initAcmeSeries();

    chartView->setChart(chart);
    chartView->update();

    if(oldChart != nullptr) {
        oldChart->removeAllSeries();
        delete oldChart;
    }
}


void CandleGraphBuilder::initAxes()
{
    chart->createDefaultAxes();

    axisTime = qobject_cast<QtCharts::QBarCategoryAxis *>(chart->axes(Qt::Horizontal).at(0));
    axisTime->setCategories(categories);
    axisTime->setTitleText("Час");

    axisValue = qobject_cast<QtCharts::QValueAxis *>(chart->axes(Qt::Vertical).at(0));
    axisValue->setMax(axisValue->max() * 1.01);
    axisValue->setMin(axisValue->min() * 0.99);

    //axisDate = new QtCharts::QDateTimeAxis();
    //axisDate->setFormat("dd-MM");
    //axisDate->setTitleText("Дата");
    //chart->addAxis(axisDate, Qt::AlignBottom);
    //acmeSeries->attachAxis(axisDate);
}


ChartView* CandleGraphBuilder::getGraphChartView()
{
    return chartView;
}


void CandleGraphBuilder::refresh_graph_builder()
{
    acmeSeries->clear();
    list_candlestick_set.clear();
    categories.clear();
}


void CandleGraphBuilder::initAcmeSeries()
{
    acmeSeries = new QtCharts::QCandlestickSeries();
    acmeSeries->setName("Графік змінення ціни монети");
    acmeSeries->setIncreasingColor(QColor(Qt::green));
    acmeSeries->setDecreasingColor(QColor(Qt::red));
}


void CandleGraphBuilder::addAllCandleStickSets(QList<QtCharts::QCandlestickSet*> list)
{
    for(QtCharts::QCandlestickSet* candlestickset : list)
    {
        list_candlestick_set.append(candlestickset);
        acmeSeries->append(candlestickset);
        categories << QDateTime::fromMSecsSinceEpoch(candlestickset->timestamp()).toString("dd.MM-hh:mm");
    }
}
