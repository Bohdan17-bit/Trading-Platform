#include "candlegraphbuilder.h"
#include <QDebug>


CandleGraphBuilder::CandleGraphBuilder()
{
    chart = nullptr;
    oldChart = nullptr;
    chartView = new ChartView();
    CandleStickList = nullptr; // adapter
    chartView->setRenderHint(QPainter::Antialiasing);
    initAcmeSeries();
}


void CandleGraphBuilder::initChartSettings()
{
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

    chartView->setChart(chart);
    chartView->update();

    if(oldChart != nullptr)
    {
        oldChart->removeAllSeries();
        delete oldChart;
    }
}


void CandleGraphBuilder::initAxes()
{
    axisValue = new QValueAxis;
    axisDate = new QDateTimeAxis;

    chart->addAxis(axisValue, Qt::AlignLeft);
    chart->addAxis(axisDate, Qt::AlignBottom);

    acmeSeries->attachAxis(axisDate);
    acmeSeries->attachAxis(axisValue);

    axisDate->setFormat("dd.MM-hh:mm");
    axisDate->setTitleText("Дата");

    axisValue->setTitleText("Ціна");
    axisValue->setMax(axisValue->max() * 1.001);
    axisValue->setMin(axisValue->min() * 0.999);

}


ChartView* CandleGraphBuilder::getGraphChartView()
{
    return chartView;
}


void CandleGraphBuilder::refresh_graph_builder()
{
    acmeSeries->clear();
    list_candlestick_set.clear();
}

void CandleGraphBuilder::refreshLastCandle(qreal open, qreal close, qreal high, qreal low)
{
    list_candlestick_set.last()->setClose(close);
    list_candlestick_set.last()->setHigh(high);
    list_candlestick_set.last()->setOpen(open);
    list_candlestick_set.last()->setLow(low);
    qDebug() << "length : after refresh" << list_candlestick_set.length();
    chartView->chart()->update();
    chartView->update();
}


void CandleGraphBuilder::insertLastCandle(qreal timestamp, qreal open, qreal close, qreal high, qreal low)
{
    QtCharts::QCandlestickSet * last_set = new QtCharts::QCandlestickSet(timestamp);
    last_set->setOpen(open);
    last_set->setClose(close);
    last_set->setHigh(high);
    last_set->setLow(low);
    acmeSeries->append(last_set);
    list_candlestick_set.append(last_set);
    chartView->chart()->update();
    chartView->update();
    qDebug() << "length : after insert" << list_candlestick_set.length();
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
    initAcmeSeries();
    for(QtCharts::QCandlestickSet* candlestickset : list)
      {
          acmeSeries->append(candlestickset);
          list_candlestick_set.append(candlestickset);
      }
}
