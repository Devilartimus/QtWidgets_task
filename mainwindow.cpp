#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "graphwidget.h"

#include <QVBoxLayout>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , graphWidget(new GraphWidget(this))
{
    ui->setupUi(this);

    QVBoxLayout *layout = new QVBoxLayout(ui->widget);
    layout->addWidget(graphWidget);

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    disconnect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);

    QString fileName = QFileDialog::getOpenFileName(this, "Открыть файл Touchstone", "", "Touchstone Files (*.s1p *.s2p)", nullptr, QFileDialog::DontUseNativeDialog);

    if (fileName.isEmpty())
    {
        ui->label->setText("Файл не выбран");
        connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
        return;
    } else
    {
        connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
    }

    if (!loadTouchstoneFile(fileName))
    {
        ui->label->setText("Ошибка при загрузке файла");
    } else {
        ui->label->setText("Файл успешно загружен");
        graphWidget->setDataPoints(dataPoints);
    }
}


bool MainWindow::loadTouchstoneFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Ошибка открытия файла";
        return false;
    }

    dataPoints.clear();

    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        if (line.startsWith("#") || line.startsWith("!"))
            continue;

        QStringList values = line.split(' ', Qt::SkipEmptyParts);
        if (values.size() >= 3)
        {
            double freq = values[0].toDouble();
            double s11Real = values[1].toDouble();
            double s11Imag = values[2].toDouble();

            double s11LogMag = 20 * log10(sqrt(s11Real * s11Real + s11Imag * s11Imag));

            dataPoints.append(QPointF(freq, s11LogMag));
        }
    }

    qDebug() << "Данные загружены: " << dataPoints.size() << " точек";
    return true;
}
