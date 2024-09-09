#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QVector>
#include <QPointF>
#include <QMessageBox>

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
    QVector<QPointF> _dataPoints;
    void drawAxis(QPainter& painter);
    void drawGraph(QPainter& painter);

    const int _RIGHT_MARGIN = 40;
    const int _LEFT_MARGIN = 20;
    const int _VERTICAL_MARGIN = 40;
};

#endif // GRAPHWIDGET_H
