#include "candles/chartview.h"
#include <QtCharts/QChartView>
#include <QApplication>
#include <QCandlestickSeries>
#include <QCandlestickSet>>
#include <QDateTime>
#include <QDateTimeAxis>
#include <QDebug>
#include <QValueAxis>

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
    QPointF mousePoint = this->mapFromGlobal(QCursor::pos());
    QtCharts::QDateTimeAxis *xAxis = qobject_cast<QtCharts::QDateTimeAxis *>(chart()->axisX());

    if (xAxis) {
        QPointF mappedPoint = chart()->mapToValue(mousePoint);
        QString dateTime = QDateTime::fromMSecsSinceEpoch(static_cast<qint64>(mappedPoint.x())).toString("dd.MM-hh:mm");
        for(int i = list_candlestick_set.count() - 1; i > 0; i--)
        {

            if(QDateTime::fromMSecsSinceEpoch(list_candlestick_set.at(i)->timestamp()).toString("dd.MM-hh:mm") == dateTime)
            {
                QGraphicsSimpleTextItem *label = dynamic_cast<QGraphicsSimpleTextItem*>(chart()->scene()->items().at(0));

                QBrush red_color_brush(Qt::red);
                QBrush green_color_brush(Qt::darkGreen);

                if(list_candlestick_set.at(i)->open() > list_candlestick_set.at(i)->close())
                {
                    label->setBrush(red_color_brush);
                }
                else
                {
                    label->setBrush(green_color_brush);
                }

                QString label_changed =
                        "open : " + QString::number(list_candlestick_set.at(i)->open()) + "   " +
                        "close : " + QString::number(list_candlestick_set.at(i)->close()) + "   " +
                        "high : " + QString::number(list_candlestick_set.at(i)->high()) + "   " +
                        "low : " + QString::number(list_candlestick_set.at(i)->low()) + "   " +
                        "time : " + dateTime;

                label->setText(label_changed);

                return;
            }
        }
    }
    if (event->buttons() & Qt::LeftButton)
    {

        auto dPos = event->pos() - m_lastMousePos;
        chart()->scroll(-dPos.x(), dPos.y());
        //
        m_lastMousePos = event->pos();
        event->accept();
        qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
    }

    QChartView::mouseMoveEvent(event);
}


void ChartView::scaleInWidth(qreal kf)
{
    QtCharts::QDateTimeAxis *axisX = qobject_cast<QtCharts::QDateTimeAxis *>(chart()->axisX());
    if (axisX)
    {
        // Отримуємо поточний діапазон дат
        const QDateTime minDate = axisX->min();
        const QDateTime maxDate = axisX->max();

        // Розраховуємо новий діапазон дат
        const qint64 diff = maxDate.toMSecsSinceEpoch() - minDate.toMSecsSinceEpoch();
        const qint64 newDiff = diff * kf;
        const qint64 delta = (newDiff - diff) / 2;
        const QDateTime newMinDate = minDate.addMSecs(-delta);
        const QDateTime newMaxDate = maxDate.addMSecs(delta);

        // Встановлюємо новий діапазон дат
        axisX->setRange(newMinDate, newMaxDate);
    }
}


bool ChartView::maxScopeRiched()
{
    QRectF plotArea = chart()->plotArea();
    QtCharts::QValueAxis *yAxis = qobject_cast<QtCharts::QValueAxis *>(chart()->axisY());
    qreal xRange = yAxis->max() - yAxis->min();
    QSizeF plotSize = plotArea.size();
    qreal xScale = plotSize.height() / xRange;
    if(xScale > 0.6)
    {
        return false;
    }
    return true;
}


bool ChartView::minScopeRiched()
{
    QRectF plotArea = chart()->plotArea();
    QtCharts::QValueAxis *yAxis = qobject_cast<QtCharts::QValueAxis *>(chart()->axisY());
    qreal xRange = yAxis->max() - yAxis->min();
    QSizeF plotSize = plotArea.size();
    qreal xScale = plotSize.height() / xRange;
    if(xScale < 2.4)
    {
        return false;
    }
    return true;
}


void ChartView::mouseReleaseEvent(QMouseEvent *event)
{
    QApplication::restoreOverrideCursor();
    emit mouseRelease();
    //QChartView::mouseReleaseEvent(event);
}

void ChartView::wheelEvent(QWheelEvent *event)
{
    qreal factor = 1;
    if(event->angleDelta().y() > 0)
    {
        factor = 1.3;
        chart()->zoom(factor);
    }
    else
    {
        factor = 0.9;
        chart()->zoom(factor);
    }
    event->accept();
    QtCharts::QChartView::wheelEvent(event);
}
