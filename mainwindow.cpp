#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->buttonBrowse, &QAbstractButton::clicked, this, &MainWindow::browse);
    connect(ui->buttonParse, &QAbstractButton::clicked, this, &MainWindow::parse);
    connect(ui->buttonPoint, &QAbstractButton::clicked, this, &MainWindow::addPoint);
    connect(ui->buttonClear, &QAbstractButton::clicked, this, &MainWindow::clear);
    connect(ui->buttonOptimize, &QAbstractButton::clicked, this, &MainWindow::optimize);
    connect(ui->buttonAddPoints, &QAbstractButton::clicked, this, &MainWindow::addRandomPoints);
    QObject::connect(this, SIGNAL(parseText(QString)), ui->widget, SLOT(parse(QString)));
    QObject::connect(this, SIGNAL(newPoint(float, float)), ui->widget, SLOT(addPoint(float,float)));
    QObject::connect(this, SIGNAL(signalclear()), ui->widget, SLOT(clear()));
    QObject::connect(this, SIGNAL(signaloptimize()), ui->widget, SLOT(optimize()));
    QObject::connect(this, SIGNAL(randomPoints(float,float,float,float,int)), ui->widget, SLOT(randomPoints(float,float,float,float,int)));
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
    float x = stof(ui->Xfloat->text().toStdString());
    float y = stof(ui->Yfloat->text().toStdString());
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
    float xmin = stof(ui->Xmin->text().toStdString());
    float xmax = stof(ui->Xmax->text().toStdString());
    float ymin = stof(ui->Ymin->text().toStdString());
    float ymax = stof(ui->Ymax->text().toStdString());

    int numberPoints = stoi(ui->numberPoint->text().toStdString());
    emit randomPoints(xmin, xmax, ymin, ymax, numberPoints);
}
