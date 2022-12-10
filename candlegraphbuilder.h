#ifndef CANDLEGRAPHBUILDER_H
#define CANDLEGRAPHBUILDER_H
#include <QList>
#include <QtCharts/QCandlestickSet>
#include <QCandlestickSeries>
#include <QDateTime>
#include <QtCharts/QChartView>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>


class CandleGraphBuilder
{
public:
    CandleGraphBuilder();
    void refresh_graph_builder();
    void addCandleStickSet(qreal timestamp, qreal open, qreal close, qreal low, qreal high);
    QtCharts::QChartView* getGraphChart();
private:
    void initCandlesGraph();
    QtCharts::QCandlestickSeries *acmeSeries;
    QStringList categories;
    QList<QtCharts::QCandlestickSet*> list_candlestick_set;
    QList<double> timestamp;
    QList<double> open;
    QList<double> close;
    QList<double> low;
    QList<double> high;
};

#endif // CANDLEGRAPHBUILDER_H
