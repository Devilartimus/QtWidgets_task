#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QVector>
#include <QPointF>

class GraphWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GraphWidget(QWidget *parent = nullptr);
    void setDataPoints(const QVector<QPointF>& points);
    void clearDataPoints();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<QPointF> dataPoints;
    void drawXY(QPainter& painter);
    void drawGraph(QPainter& painter);
};

#endif // GRAPHWIDGET_H
