#include "graphwidget.h"
#include <limits>

GraphWidget::GraphWidget(QWidget *parent) : QWidget(parent) {}

void GraphWidget::setDataPoints(const QVector<QPointF>& points)
{
    _dataPoints = points;
    update();
}

void GraphWidget::clearDataPoints()
{
    _dataPoints.clear();
    update();
}

void GraphWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.drawLine(_LEFT_MARGIN, height() - _VERTICAL_MARGIN, width() - _RIGHT_MARGIN, height() - _VERTICAL_MARGIN);
    painter.drawLine(_LEFT_MARGIN, _RIGHT_MARGIN, _LEFT_MARGIN, height() - _VERTICAL_MARGIN);

    if(!_dataPoints.isEmpty())
    {
        drawGraph(painter);
    }

    painter.setFont(QFont("Arial", 10));
    painter.drawText(width() / 2 - _LEFT_MARGIN, height() - 10, "Frequency");
    painter.save();

    painter.rotate(-90);
    painter.drawText(-height() / 2 - _VERTICAL_MARGIN, _LEFT_MARGIN / 2, "S11LogMag");
    painter.restore();
}

void GraphWidget::drawGraph(QPainter &painter)
{
    if (_dataPoints.isEmpty())
    {
        QMessageBox::critical(this, "Error", "Data points array is empty.");
        return;
    }
    double minFreq = _dataPoints[0].x();
    double maxFreq = _dataPoints[_dataPoints.size() - 1].x();
    double minLogMag = std::numeric_limits<double>::max();
    double maxLogMag = std::numeric_limits<double>::min();

    for (const QPointF &point : _dataPoints)
    {
        double logMag = point.y();
        if (logMag < minLogMag)
            minLogMag = logMag;
        if (logMag > maxLogMag)
            maxLogMag = logMag;
    }

    for (int i = 1; i < _dataPoints.size(); i++)
    {
        QPoint p1 = QPoint(_LEFT_MARGIN + (_dataPoints[i - 1].x() - minFreq) / (maxFreq - minFreq) * (width() - _LEFT_MARGIN - _RIGHT_MARGIN),
                           height() - _VERTICAL_MARGIN - (_dataPoints[i - 1].y() - minLogMag) / (maxLogMag - minLogMag) * (height() - 60));

        QPoint p2 = QPoint(_LEFT_MARGIN + (_dataPoints[i].x() - minFreq) / (maxFreq - minFreq) * (width() - _LEFT_MARGIN - _RIGHT_MARGIN),
                           height() - _VERTICAL_MARGIN - (_dataPoints[i].y() - minLogMag) / (maxLogMag - minLogMag) * (height() - 60));
        painter.drawLine(p1, p2);
    }
}
