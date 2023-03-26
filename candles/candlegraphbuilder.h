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
    void setLimitPoints(int number_points);
    void addAllCandleStickSets(QList<QtCharts::QCandlestickSet*> list);
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
    QtCharts::QBarCategoryAxis *axisTime;
    QtCharts::QDateTimeAxis *axisDate;
    QtCharts::QValueAxis *axisValue;
    QStringList categories;
    QList<QtCharts::QCandlestickSet*> list_candlestick_set;
    QList<double> timestamp;
    QList<double> open;
    QList<double> close;
    QList<double> low;
    QList<double> high;
};

#endif // CANDLEGRAPHBUILDER_H
