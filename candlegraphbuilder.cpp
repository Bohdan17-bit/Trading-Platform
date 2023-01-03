#include "candlegraphbuilder.h"
#include <QDebug>


CandleGraphBuilder::CandleGraphBuilder()
{
    chart = nullptr;
    oldChart = nullptr;
    chartView = new QtCharts::QChartView();
    chartView->setRenderHint(QPainter::Antialiasing);
    initAcmeSeries();
}


void CandleGraphBuilder::initChartSettings()
{
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
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

    QtCharts::QBarCategoryAxis *axisTime = qobject_cast<QtCharts::QBarCategoryAxis *>(chart->axes(Qt::Horizontal).at(0));
    axisTime->setCategories(categories);

    QtCharts::QValueAxis *axisValue = qobject_cast<QtCharts::QValueAxis *>(chart->axes(Qt::Vertical).at(0));
    axisValue->setMax(axisValue->max() * 1.01);
    axisValue->setMin(axisValue->min() * 0.99);
}


QtCharts::QChartView* CandleGraphBuilder::getGraphChartView()
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


void CandleGraphBuilder::addCandleStickSet(qreal timestamp, qreal open, qreal close, qreal low, qreal high)
{
    QtCharts::QCandlestickSet * candlestickset = new QtCharts::QCandlestickSet(timestamp);
    candlestickset->setOpen(open);
    candlestickset->setHigh(high);
    candlestickset->setLow(low);
    candlestickset->setClose(close);
    list_candlestick_set.append(candlestickset);
    acmeSeries->append(candlestickset);
    categories << QDateTime::fromMSecsSinceEpoch(candlestickset->timestamp()).toString("hh:mm");
}
