#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "graphwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    graphWidget(new GraphWidget(this))
{
    ui->setupUi(this);

    this->setFixedSize(800,600);

    setWindowTitle("Graph display");

    ui->statusbar->showMessage(tr("Select file"));

    QVBoxLayout *layout = new QVBoxLayout(ui->widget);
    layout->addWidget(graphWidget);

    connect(ui->LoadButton, &QPushButton::clicked, this, &MainWindow::onLoadButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onLoadButtonClicked()
{
    graphWidget->clearDataPoints();

    //according to Touchstone spec : https://ibis.org/connector/touchstone_spec11.pdf
    //Touchstone file can have extensions as .s1p and .s2p
    QString filename = QFileDialog::getOpenFileName(this, "Open Touchstone file", "", "Touchstone Files (*.s1p *.s2p)", nullptr, QFileDialog::DontUseNativeDialog);

    if (filename.isEmpty())
    {
        ui->statusbar->showMessage(tr("File not selected"));
        QMessageBox::warning(this, "Error", "File not selected");
        return;
    }

    auto points = loadTouchstoneFile(filename);

    if (points.isEmpty())
    {
        ui->statusbar->showMessage(tr("Error while loading the file"));
        QMessageBox::critical(this, "Error", "Unable to load the file. Check it's format and try again.");
        return;
    }

    graphWidget->setDataPoints(points);
    ui->statusbar->showMessage(tr("File succesfully loaded"));
    setWindowTitle("Graph: " + filename);
}

QVector<QPointF> MainWindow::loadTouchstoneFile(const QString &filename)
{
    QVector<QPointF> points{};

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return points;


    QTextStream in(&file);

    while (!in.atEnd())
    {
        QString line = in.readLine();
        if (line.startsWith("#") || line.startsWith("!"))
            continue;

        QStringList values = line.split(' ', Qt::SkipEmptyParts);
        if (values.size() < 3)
            return points;

        bool check{};

        double freq = values[0].toDouble(&check);
        if (!check)
            return points;

        double s11Real = values[1].toDouble(&check);
        if (!check)
            return points;

        double s11Imag = values[2].toDouble(&check);
        if (!check)
            return points;

        double s11LogMag = 20 * log10(abs(sqrt(s11Real * s11Real + s11Imag * s11Imag)));

        points.append(QPointF(freq, s11LogMag));
    }
    return points;
}

