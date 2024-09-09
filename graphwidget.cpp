#include "graphwidget.h"

GraphWidget::GraphWidget(QWidget *parent) : QWidget(parent) {}

void GraphWidget::setDataPoints(const QVector<QPointF>& points)
{
    dataPoints = points;
    update();
}

void GraphWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.drawLine(10, height() - 10, width() - 10, height() - 10);
    painter.drawLine(10, 10, 10, height() - 10);

    if (dataPoints.size() > 1)
    {
        for (int i = 1; i < dataPoints.size(); ++i)
        {
            QPoint p1 = QPoint(10 + (dataPoints[i - 1].x() * (width() - 20) / 100), height() - 10 - (dataPoints[i - 1].y() * (height() - 20) / 100));
            QPoint p2 = QPoint(10 + (dataPoints[i].x() * (width() - 20) / 100), height() - 10 - (dataPoints[i].y() * (height() - 20) / 100));
            painter.drawLine(p1, p2);
        }
    }
}
