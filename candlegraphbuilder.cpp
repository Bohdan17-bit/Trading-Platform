#include "candlegraphbuilder.h"
#include <QDebug>

CandleGraphBuilder::CandleGraphBuilder()
{
    initCandlesGraph();
}

QtCharts::QChartView* CandleGraphBuilder::getGraphChart()
{
    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(acmeSeries);
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);
    chart->createDefaultAxes();
    QtCharts::QBarCategoryAxis *axisX = qobject_cast<QtCharts::QBarCategoryAxis *>(chart->axes(Qt::Horizontal).at(0));
    axisX->setCategories(categories);

    QtCharts::QValueAxis *axisY = qobject_cast<QtCharts::QValueAxis *>(chart->axes(Qt::Vertical).at(0));
    axisY->setMax(axisY->max() * 1.01);
    axisY->setMin(axisY->min() * 0.99);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    return chartView;
}

void CandleGraphBuilder::refresh_graph_builder()
{
    acmeSeries->remove(list_candlestick_set);
    list_candlestick_set.clear();
    categories.clear();
}

void CandleGraphBuilder::initCandlesGraph()
{
    acmeSeries = new QtCharts::QCandlestickSeries();
    acmeSeries->setName("Графік змінення ціни монети");
    acmeSeries->setIncreasingColor(QColor(Qt::green));
    acmeSeries->setDecreasingColor(QColor(Qt::red));
    qDebug() << "Графік ініціалізовано. Все ок.";
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
