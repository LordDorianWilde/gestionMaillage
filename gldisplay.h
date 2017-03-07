#ifndef GLDISPLAY_H
#define GLDISPLAY_H

#include <QGLWidget>
#include <gasket.h>
#include <QtConcurrent/qtconcurrentrun.h>
#include <QMouseEvent>


class GLDisplay : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLDisplay(QWidget *parent = 0);

    virtual void initializeGL();

    virtual void paintGL();

    virtual void resizeGL(int w, int h);

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Gasket gasket;
    bool mousePressed;
    QPoint lastPos;
    double translateX;
    double translateY;
    double zoom;
    
signals:
    
public slots:
    void parse(QString filename);
    void addPoint(double x, double y);
    void clear();
    void optimize();
    void receiveZoom(double);
    void randomPoints(double, double, double, double, int);
    void crust();
    void incDelaunay(bool);
    
};

#endif // GLDISPLAY_H
