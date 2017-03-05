#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    void browse();
    void parse();
    void addPoint();
    void clear();
    void optimize();
    void addRandomPoints();
    ~MainWindow();

signals:
    void parseText(QString);
    void newPoint(float, float);
    void signalclear();
    void signaloptimize();
    void randomPoints(float, float, float, float, int);
    
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
