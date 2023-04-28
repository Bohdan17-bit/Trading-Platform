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

void ChartView::setNewLabel(QtCharts::QCandlestickSet *set, QString dateTime)
{
    QGraphicsSimpleTextItem *label = dynamic_cast<QGraphicsSimpleTextItem*>(chart()->scene()->items().at(0));

    QBrush red_color_brush(Qt::red);
    QBrush green_color_brush(Qt::darkGreen);

    if(set->open() > set->close())
    {
        label->setBrush(red_color_brush);
    }
    else
    {
        label->setBrush(green_color_brush);
    }

    QString label_changed =
            "open : " + QString::number(set->open()) + "   " +
            "close : " + QString::number(set->close()) + "   " +
            "high : " + QString::number(set->high()) + "   " +
            "low : " + QString::number(set->low()) + "   " +
            "time : " + dateTime;

    label->setText(label_changed);
}


void ChartView::mouseMoveEvent(QMouseEvent *event)
{
    QPointF mousePoint = this->mapFromGlobal(QCursor::pos());
    QtCharts::QDateTimeAxis *xAxis = qobject_cast<QtCharts::QDateTimeAxis *>(chart()->axisX());

    if (xAxis) {
        QPointF mappedPoint = chart()->mapToValue(mousePoint);
        QString dateTime;
        if(mode == "2_HOURS")
        {
            dateTime = QDateTime::fromMSecsSinceEpoch(static_cast<qint64>(mappedPoint.x())).toString("dd.MM-hh:00");
        }
        else
        {
            dateTime = QDateTime::fromMSecsSinceEpoch(static_cast<qint64>(mappedPoint.x())).toString("dd.MM-hh:mm");
        }
        for(int i = list_candlestick_set.count() - 1; i > 0; i--)
        {
            if(mode == "2_HOURS")
            {
                if(QDateTime::fromMSecsSinceEpoch(list_candlestick_set.at(i)->timestamp()).toString("dd.MM-hh:00") == dateTime)
                {
                    setNewLabel(list_candlestick_set.at(i), dateTime);
                    return;
                }
            }
            else
            {
                if(QDateTime::fromMSecsSinceEpoch(list_candlestick_set.at(i)->timestamp()).toString("dd.MM-hh:mm") == dateTime)
                {
                    setNewLabel(list_candlestick_set.at(i), dateTime);
                    return;
                }
            }
        }
    }

    if (event->buttons() & Qt::LeftButton)
       {

           auto dPos = event->pos() - m_lastMousePos;
           chart()->scroll(-dPos.x(), dPos.y());
           setRangeForValueAxis();
           m_lastMousePos = event->pos();
           event->accept();
           qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
       }

       QChartView::mouseMoveEvent(event);
}


void ChartView::setRangeForValueAxis()
{
    QtCharts::QValueAxis *axisY = qobject_cast<QtCharts::QValueAxis *>(chart()->axisY());

    qreal min = list_candlestick_set.last()->low();
    qreal max = list_candlestick_set.last()->high();

    QtCharts::QDateTimeAxis *xAxis = qobject_cast<QtCharts::QDateTimeAxis *>(chart()->axisX());
    QDateTime min_x = xAxis->min();
    QDateTime max_x = xAxis->max();


    for(int i = list_candlestick_set.count() - 1; i > 0; i--)
    {
        if(QDateTime::fromMSecsSinceEpoch(list_candlestick_set.at(i)->timestamp()) > min_x
                && QDateTime::fromMSecsSinceEpoch(list_candlestick_set.at(i)->timestamp()) < max_x)
        {
            if(list_candlestick_set.at(i)->high() > max)
            {
                max = list_candlestick_set.at(i)->high();
            }
            if(list_candlestick_set.at(i)->low() < min)
            {
                min = list_candlestick_set.at(i)->low();
            }
        }
    }

    qDebug() << "new max : " << max;
    qDebug() << "new min: " << min;

    qreal delta = (max - min) * 0.05;
    min -= delta ;
    max += delta;
    qDebug() << "new max after sub : " << max;
    qDebug() << "new min after sub: " << min;

    axisY->setRange(min, max);
}


bool ChartView::maxScopeRiched()
{
    QtCharts::QDateTimeAxis *axisX = qobject_cast<QtCharts::QDateTimeAxis *>(chart()->axisX());
    if (axisX)
    {
        // Отримуємо поточний діапазон дат
        const QDateTime minDate = axisX->min();
        const QDateTime maxDate = axisX->max();

        if(mode == "15_MINUTES")
        {
            if(maxDate.toSecsSinceEpoch() - minDate.toSecsSinceEpoch() < 36 * 60 * 60) // 36 hours range
            {
                return true;
            }
        }
        else if(mode == "2_HOURS")
        {
            if(maxDate.toSecsSinceEpoch() - minDate.toSecsSinceEpoch() < 10 * 24 * 60 * 60) // 10 days range
            {
                return true;
            }
        }
        else if(mode == "5_MINUTES")
        {
            if(maxDate.toSecsSinceEpoch() - minDate.toSecsSinceEpoch() < 10 * 60 * 60) // 10 hours range
            {
                return true;
            }
        }
        return false;
    }
}


bool ChartView::minScopeRiched()
{
    QtCharts::QDateTimeAxis *axisX = qobject_cast<QtCharts::QDateTimeAxis *>(chart()->axisX());
    if (axisX)
    {
        // Отримуємо поточний діапазон дат
        const QDateTime minDate = axisX->min();
        const QDateTime maxDate = axisX->max();

        if(mode == "15_MINUTES")
        {
            if(maxDate.toSecsSinceEpoch() - minDate.toSecsSinceEpoch() > 12 * 60 * 60) // 5 hours range
            {
                return true;
            }
        }
        else if(mode == "2_HOURS")
        {
            if(maxDate.toSecsSinceEpoch() - minDate.toSecsSinceEpoch() > 4 * 24 * 60 * 60) // 4 days range
            {
                return true;
            }
        }
        else if(mode == "5_MINUTES")
        {
            if(maxDate.toSecsSinceEpoch() - minDate.toSecsSinceEpoch() > 4 * 60 * 60) // 4 hours range
            {
                return true;
            }
        }
        return false;
    }
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
        if(minScopeRiched())
        {
            factor = 1.1;
            chart()->zoom(factor);
            setRangeForValueAxis();
        }
    }
    else
    {
        if(maxScopeRiched())
        {
            factor = 0.9;
            chart()->zoom(factor);
            setRangeForValueAxis();
        }
    }
    event->accept();
    QtCharts::QChartView::wheelEvent(event);
}
