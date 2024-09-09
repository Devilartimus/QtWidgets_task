#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "graphwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    graphWidget(new GraphWidget(this))
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
    QString filename = QFileDialog::getOpenFileName(this, "Выберите файл Touchstone", "", "Touchstone Files (*.s1p *.s2p)");

    if (filename.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Файл не выбран");
        return;
    }

    if (!loadTouchstoneFile(filename))
    {
        QMessageBox::critical(this, "Ошибка", "Невозможно загрузить файл. Проверьте формат и повторите попытку.");
    } else
    {
        QVector<QPointF> points;

        graphWidget->setDataPoints(points);
        ui->label->setText("Файл успешно загружен");
    }
}

bool MainWindow::loadTouchstoneFile(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&file);
    QVector<QPointF> points;

    while (!in.atEnd())
    {
        QString line = in.readLine();
        if (line.startsWith("#") || line.startsWith("!"))
            continue;

        QStringList values = line.split(' ', Qt::SkipEmptyParts);
        if (values.size() < 3)
            return false;

        bool check;

        double freq = values[0].toDouble(&check);
        if (!check)
            return false;

        double s11Real = values[1].toDouble(&check);
        if (!check)
            return false;

        double s11Imag = values[2].toDouble(&check);
        if (!check)
            return false;

        double s11LogMag = 20 * log10(sqrt(s11Real * s11Real + s11Imag * s11Imag));

        points.append(QPointF(freq, s11LogMag));
    }

    graphWidget->setDataPoints(points);
    return true;
}
