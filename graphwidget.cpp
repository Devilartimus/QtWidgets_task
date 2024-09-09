#include "graphwidget.h"
#include <limits>

GraphWidget::GraphWidget(QWidget *parent) : QWidget(parent) {}

void GraphWidget::setDataPoints(const QVector<QPointF>& points)
{
    dataPoints = points;
    update();
}

void GraphWidget::clearDataPoints()
{
    dataPoints.clear();
    update();
}

void GraphWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    drawXY(painter);
    if(!dataPoints.isEmpty())
        drawGraph(painter);
}

void GraphWidget::drawXY(QPainter &painter)
{
    painter.drawLine(10, height() - 10, width() - 10, height() - 10);
    painter.drawLine(10, 10, 10, height() - 10);
}

void GraphWidget::drawGraph(QPainter &painter)
{
    double minFreq = dataPoints[0].x();
    double maxFreq = dataPoints[dataPoints.size() - 1].x();
    double minLogMag = std::numeric_limits<double>::max();
    double maxLogMag = std::numeric_limits<double>::min();

    for (const QPointF &point : dataPoints)
    {
        double logMag = point.y();
        if (logMag < minLogMag)
            minLogMag = logMag;
        if (logMag > maxLogMag)
            maxLogMag = logMag;
    }

    for (int i = 1; i < dataPoints.size(); i++)
    {
        QPoint p1 = QPoint(10 + (dataPoints[i - 1].x() - minFreq) / (maxFreq - minFreq) * (width() - 20),
                            height() - 10 - (dataPoints[i - 1].y() - minLogMag) / (maxLogMag - minLogMag) * (height() - 20));
        QPoint p2 = QPoint(10 + (dataPoints[i].x() - minFreq) / (maxFreq - minFreq) * (width() - 20),
                           height() - 10 - (dataPoints[i].y() - minLogMag) / (maxLogMag - minLogMag) * (height() - 20));
        painter.drawLine(p1, p2);
    }
}
