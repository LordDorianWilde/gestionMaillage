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

protected:
    void keyPressEvent(QKeyEvent *event);
    
public:
    explicit MainWindow(QWidget *parent = 0);
    void browse();
    void parse();
    void addPoint();
    void clear();
    void optimize();
    void addRandomPoints();
    ~MainWindow();
    double zoom;

signals:
    void parseText(QString);
    void newPoint(double, double);
    void signalclear();
    void signaloptimize();
    void randomPoints(double, double, double, double, int);
    void sendZoom(double);
    
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
