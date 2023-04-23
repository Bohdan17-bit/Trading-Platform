#include "candles/chartview.h"
#include <QtCharts/QChartView>
#include <QApplication>
#include <QDebug>

void ChartView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
     {
         QApplication::setOverrideCursor(QCursor(Qt::SizeAllCursor));
         m_lastMousePos = event->pos();
         event->accept();
         emit mousePress();
     }

     QChartView::mousePressEvent(event);
}

void ChartView::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {

        auto dPos = event->pos() - m_lastMousePos;
        chart()->scroll(-dPos.x(), 0);

        m_lastMousePos = event->pos();
        event->accept();
        qApp->processEvents(QEventLoop::ExcludeUserInputEvents);

    }

    QChartView::mouseMoveEvent(event);
}

void ChartView::mouseReleaseEvent(QMouseEvent *event)
{
    QApplication::restoreOverrideCursor();
    emit mouseRelease();
    //QChartView::mouseReleaseEvent(event);
}

void ChartView::wheelEvent(QWheelEvent *event)
{
    qreal factor = event->angleDelta().y() > 0? 2: 0.5;
    chart()->zoom(factor);
    event->accept();
    QtCharts::QChartView::wheelEvent(event);
}
