#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    zoom = 1;
    ui->setupUi(this);
    connect(ui->buttonBrowse, &QAbstractButton::clicked, this, &MainWindow::browse);
    connect(ui->buttonParse, &QAbstractButton::clicked, this, &MainWindow::parse);
    connect(ui->buttonPoint, &QAbstractButton::clicked, this, &MainWindow::addPoint);
    connect(ui->buttonClear, &QAbstractButton::clicked, this, &MainWindow::clear);
    connect(ui->buttonOptimize, &QAbstractButton::clicked, this, &MainWindow::optimize);
    connect(ui->checkDelaunay, &QAbstractButton::clicked, this, &MainWindow::delaunayInc);
    connect(ui->buttonAddPoints, &QAbstractButton::clicked, this, &MainWindow::addRandomPoints);
    QObject::connect(this, SIGNAL(parseText(QString)), ui->widget, SLOT(parse(QString)));
    QObject::connect(this, SIGNAL(sendZoom(double)), ui->widget, SLOT(receiveZoom(double)));
    QObject::connect(this, SIGNAL(newPoint(double, double)), ui->widget, SLOT(addPoint(double,double)));
    QObject::connect(this, SIGNAL(signalclear()), ui->widget, SLOT(clear()));
    QObject::connect(this, SIGNAL(signaloptimize()), ui->widget, SLOT(optimize()));
    QObject::connect(this, SIGNAL(randomPoints(double,double,double,double,int)), ui->widget, SLOT(randomPoints(double,double,double,double,int)));
    QObject::connect(ui->buttonCrush, SIGNAL(clicked()), ui->widget, SLOT(crust()));
    QObject::connect(this, SIGNAL(delaunay(bool)), ui->widget, SLOT(incDelaunay(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::browse()
{
    QString directory = QFileDialog::getOpenFileName(this,tr("Open Text file"), "", tr("Text Files (*.off)"));

    if (!directory.isEmpty()) {
        if (ui->comboBox->findText(directory) == -1)
            ui->comboBox->addItem(directory);
        ui->comboBox->setCurrentIndex(ui->comboBox->findText(directory));
    }
}

void MainWindow::parse()
{
    emit parseText(ui->comboBox->currentText());
}

void MainWindow::addPoint()
{
    double x = stod(ui->Xfloat->text().toStdString());
    double y = stod(ui->Yfloat->text().toStdString());
    emit newPoint(x, y);
}

void MainWindow::clear()
{
    emit signalclear();
}

void MainWindow::optimize()
{
    emit signaloptimize();
}

void MainWindow::addRandomPoints()
{
    double xmin = stod(ui->Xmin->text().toStdString());
    double xmax = stod(ui->Xmax->text().toStdString());
    double ymin = stod(ui->Ymin->text().toStdString());
    double ymax = stod(ui->Ymax->text().toStdString());

    int numberPoints = stoi(ui->numberPoint->text().toStdString());
    emit randomPoints(xmin, xmax, ymin, ymax, numberPoints);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == 43)
    {
        zoom *= 1.5;
    }
    else if(event->key() == 45)
    {
        zoom /= 1.5;
    }
    emit sendZoom(zoom);
}

void MainWindow::delaunayInc()
{
    emit delaunay(ui->checkDelaunay->checkState() == Qt::Checked);
}
