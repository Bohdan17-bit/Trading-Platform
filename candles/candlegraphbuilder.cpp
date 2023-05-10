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


    axisDate->setMin(QDateTime::fromMSecsSinceEpoch
                     (chartView->list_candlestick_set.at(chartView->list_candlestick_set.count() - 50)->timestamp()));
    axisDate->setMax(QDateTime::fromMSecsSinceEpoch
                     (chartView->list_candlestick_set.at(chartView->list_candlestick_set.count() - 1)->timestamp()));

    chartView->setRangeForValueAxis();

    if(oldChart != nullptr)
    {
        oldChart->removeAllSeries();
        delete oldChart;
    }

    QGraphicsSimpleTextItem *candle = new QGraphicsSimpleTextItem("");
    QFont font("Verdana", 10);
    candle->setPos(105, 45);
    candle->setFont(font);
    chart->scene()->addItem(candle);

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
    axisDate->setTitleText("Date");

    axisValue->setTitleText("Price");

}


ChartView* CandleGraphBuilder::getGraphChartView()
{
    return chartView;
}


void CandleGraphBuilder::refresh_graph_builder()
{
    acmeSeries->clear();
    chartView->list_candlestick_set.clear();
}

void CandleGraphBuilder::refreshLastCandle(qreal open, qreal close, qreal high, qreal low)
{
    chartView->list_candlestick_set.last()->setClose(close);
    chartView->list_candlestick_set.last()->setHigh(high);
    chartView->list_candlestick_set.last()->setOpen(open);
    chartView->list_candlestick_set.last()->setLow(low);
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
    chartView->list_candlestick_set.append(last_set);
    chartView->chart()->update();
    chartView->update();
}


void CandleGraphBuilder::initAcmeSeries()
{
    acmeSeries = new QtCharts::QCandlestickSeries();
    acmeSeries->setName("Coin price chart");
    acmeSeries->setIncreasingColor(QColor(Qt::green));
    acmeSeries->setDecreasingColor(QColor(Qt::red));
}


void CandleGraphBuilder::addAllCandleStickSets(QList<QtCharts::QCandlestickSet*> list)
{
    initAcmeSeries();
    for(QtCharts::QCandlestickSet* candlestickset : list)
      {
          acmeSeries->append(candlestickset);
          chartView->list_candlestick_set.append(candlestickset);
      }
}
