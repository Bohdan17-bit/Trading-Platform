#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QtCharts/QChartView>

#include <QCandlestickSet>

class ChartView : public QtCharts::QChartView
{
    Q_OBJECT
public:
    ChartView()
    {
        mode = "15_MINUTES";
        m_lastMousePos.setX(0);
        m_lastMousePos.setY(0);
    }
    QList<QtCharts::QCandlestickSet*> list_candlestick_set;
    QString mode;
    void setRangeForValueAxis();
public slots:
    void handleHovered(bool status, QtCharts::QCandlestickSet *set);
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void wheelEvent(QWheelEvent *event) override;
private:
    QPointF m_lastMousePos;
    bool maxScopeRiched();
    bool minScopeRiched();
    void setNewLabel(QtCharts::QCandlestickSet *set);

signals:
    void mousePress();
    void mouseRelease();
};


#endif // CHARTVIEW_H
