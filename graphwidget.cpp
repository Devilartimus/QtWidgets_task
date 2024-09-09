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

    painter.drawLine(40, height() - 40, width() - 20, height() - 40);
    painter.drawLine(40, 20, 40, height() - 40);

    if(!dataPoints.isEmpty())
    {
        drawGraph(painter);
    }

    painter.setFont(QFont("Arial", 10));
    painter.drawText(width() / 2 - 40, height() - 10, "Frequency");
    painter.save();

    painter.rotate(-90);
    painter.drawText(-height() / 2 - 40, 20, "S11LogMag");
    painter.restore();
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
        QPoint p1 = QPoint(40 + (dataPoints[i - 1].x() - minFreq) / (maxFreq - minFreq) * (width() - 60),
                           height() - 40 - (dataPoints[i - 1].y() - minLogMag) / (maxLogMag - minLogMag) * (height() - 60));
        QPoint p2 = QPoint(40 + (dataPoints[i].x() - minFreq) / (maxFreq - minFreq) * (width() - 60),
                           height() - 40 - (dataPoints[i].y() - minLogMag) / (maxLogMag - minLogMag) * (height() - 60));
        painter.drawLine(p1, p2);
    }
}
