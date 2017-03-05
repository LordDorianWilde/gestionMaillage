#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->buttonBrowse, &QAbstractButton::clicked, this, &browse);
    connect(ui->buttonParse, &QAbstractButton::clicked, this, &parse);
    connect(ui->buttonPoint, &QAbstractButton::clicked, this, &addPoint);
    QObject::connect(this, SIGNAL(parseText(QString)), ui->widget, SLOT(parse(QString)));
    QObject::connect(this, SIGNAL(newPoint(float, float)), ui->widget, SLOT(addPoint(float,float)));
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
