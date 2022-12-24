#ifndef PIECHARTWINDOW_H
#define PIECHARTWINDOW_H

#include <QMainWindow>
#include "drilldownchart.h"
#include "drilldownslice.h"
#include <QtCharts/QChartView>

namespace Ui {
class PiechartWindow;
}

class PiechartWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PiechartWindow(QWidget *parent = nullptr);
    ~PiechartWindow();
    void getCoins(QVector<QPair<QString, double>> coins);

private:
    void initSettingsChart();
    void initSettingsPieSeries();
    void drawDiagram(QVector<QPair<QString, double>> coins);

private:
    Ui::PiechartWindow *ui;
    DrillDownChart *chart;
    QPieSeries *coinSeries;
    QChartView *chartView;
};

#endif // PIECHARTWINDOW_H
