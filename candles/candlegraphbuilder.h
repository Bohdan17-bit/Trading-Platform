#ifndef CANDLEGRAPHBUILDER_H
#define CANDLEGRAPHBUILDER_H
#include <QList>
#include <QtCharts/QCandlestickSet>
#include <QCandlestickSeries>
#include <QDateTime>
#include <QtCharts/QChartView>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QDateTimeAxis>
#include "candles/chartview.h"
#include "candles/candlesticklist.h"


class CandleGraphBuilder
{
public:
    CandleGraphBuilder();
    void refresh_graph_builder();
    void createNewChart();
    void addAllCandleStickSets(QList<QtCharts::QCandlestickSet*> list);
    void refreshLastCandle(qreal open, qreal close, qreal high, qreal low);
    void insertLastCandle(qreal timestamp, qreal open, qreal close, qreal high, qreal low);
    ChartView* getGraphChartView();
    CandleStickList *CandleStickList; // adapter
private:
    void initAcmeSeries();
    void initAxes();
    void initChartSettings();
    ChartView *chartView;
    QtCharts::QChart *chart;
    QtCharts::QChart *oldChart;
    QtCharts::QCandlestickSeries *acmeSeries;
    QtCharts::QDateTimeAxis *axisDate;
    QtCharts::QValueAxis *axisValue;
    QList<QtCharts::QCandlestickSet*> list_candlestick_set;
};

#endif // CANDLEGRAPHBUILDER_H
