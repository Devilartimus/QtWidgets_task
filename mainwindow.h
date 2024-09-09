#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QPainter>
#include <QLabel>
#include <QWidget>

#include "graphwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    GraphWidget *graphWidget;
    QVector<QPointF> dataPoints;
    bool loadTouchstoneFile(const QString &fileName);
    bool isFileLoading = false;
};

#endif // MAINWINDOW_H
