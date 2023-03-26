#ifndef PIECHARTWINDOW_H
#define PIECHARTWINDOW_H

#include <QMainWindow>
#include "piechart/drilldownchart.h"
#include "piechart/drilldownslice.h"
#include <QtCharts/QChartView>
#include "utils/sound.h"

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
    void getSoundObj(Sound *sound);
    void closeEvent(QCloseEvent *event) override;

private:
    void initSettingsChart();
    void initSettingsPieSeries();
    void drawDiagram(QVector<QPair<QString, double>> coins);

private:
    Ui::PiechartWindow *ui;
    DrillDownChart *chart;
    QPieSeries *coinSeries;
    QChartView *chartView;
    Sound *sound;
};

#endif // PIECHARTWINDOW_H
