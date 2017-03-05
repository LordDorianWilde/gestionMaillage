#ifndef GLDISPLAY_H
#define GLDISPLAY_H

#include <QGLWidget>
#include <gasket.h>
#include <QMouseEvent>
#include <random>

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
    float translateX;
    float translateY;
    std::default_random_engine generator;
    
signals:
    
public slots:
    void parse(QString filename);
    void addPoint(float x, float y);
    void clear();
    void optimize();
    void randomPoints(float, float, float, float, int);
    
};

#endif // GLDISPLAY_H
