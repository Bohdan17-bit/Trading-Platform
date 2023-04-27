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
        m_lastMousePos.setX(0);
        m_lastMousePos.setY(0);
    }
    QList<QtCharts::QCandlestickSet*> list_candlestick_set;

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void wheelEvent(QWheelEvent *event) override;
private:
    QPointF m_lastMousePos;
    void scaleInWidth(qreal cf);
    bool maxScopeRiched();
    bool minScopeRiched();

signals:
    void mousePress();
    void mouseRelease();
};


#endif // CHARTVIEW_H
