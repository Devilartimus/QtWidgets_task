#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QVBoxLayout>

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
    void onLoadButtonClicked();

private:
    Ui::MainWindow *ui;
    GraphWidget *graphWidget;
    QVector<QPointF> loadTouchstoneFile(const QString &fileName);
};

#endif // MAINWINDOW_H
