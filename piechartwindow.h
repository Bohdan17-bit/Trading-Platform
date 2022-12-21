#ifndef PIECHARTWINDOW_H
#define PIECHARTWINDOW_H

#include <QWidget>
#include "drilldownchart.h"
#include "drilldownslice.h"

namespace Ui {
class PiechartWindow;
}

class PiechartWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PiechartWindow(QWidget *parent = nullptr);
    ~PiechartWindow();

private:
    void initSettingsChart();
    void initSettingsPieSeries();

private:
    Ui::PiechartWindow *ui;
    DrillDownChart *chart;
    QPieSeries *coinSeries;
};

#endif // PIECHARTWINDOW_H
