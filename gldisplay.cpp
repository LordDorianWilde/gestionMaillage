#include "gldisplay.h"

GLDisplay::GLDisplay(QWidget *parent) :
    QGLWidget(parent)
{
    mousePressed = false;
    translateX = 0.0;
    translateY = 0.0;
    zoom = 1.0;

}

void GLDisplay::initializeGL()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glColor3f(0.0, 0.0, 0.0);
}

void GLDisplay::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    gasket.translateX = -translateX;
    gasket.translateY = translateY;
    gasket.zoom = zoom;
    gasket.draw();

    update();

}

void GLDisplay::parse(QString filename)
{
    gasket.clear();
    gasket.parseFichier(filename);
}

void GLDisplay::addPoint(double x, double y)
{
    gasket.addPoint(x, y);
}

void GLDisplay::clear()
{
    gasket.clear();
}

void GLDisplay::optimize()
{
    QFuture<void> future = QtConcurrent::run(&gasket, &Gasket::optimize);
    //gasket.optimize();
}

void GLDisplay::randomPoints(double xmin, double xmax, double ymin, double ymax, int number)
{
    gasket.addPoint( xmin, xmax, ymin, ymax, number);
}

void GLDisplay::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void GLDisplay::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::RightButton) {
        double a = event->pos().x() * 2;
        double b = event->pos().y() * 2;
        double w = (this->width());
        double h = (this->height());
        double x = ((a/w)-1) / zoom-translateX;
        double y = -((b/h)-1) / zoom+translateY;
        gasket.addPoint(x,y);
        return;
    }
    lastPos = event->pos();
    mousePressed = true;

}

void GLDisplay::mouseMoveEvent(QMouseEvent *event)
{
    if(mousePressed)
    {
        double a = (event->pos().x() - lastPos.x()) * 2;
        double b = (event->pos().y() - lastPos.y()) * 2;
        double w = (this->width());
        double h = (this->height());
        double x = a / (w*zoom);
        double y = b / (h*zoom);
        translateX += x;
        translateY += y;
    }
    lastPos = event->pos();
}

void GLDisplay::mouseReleaseEvent(QMouseEvent *event)
{
    lastPos = event->pos();
    mousePressed = false;
}

void GLDisplay::receiveZoom(double z)
{
    zoom = z;
    qDebug() <<" gld zoom : " << zoom;
}

void GLDisplay::crust() {
    this->gasket.crust();
}

void GLDisplay::incDelaunay(bool a)
{
    gasket.incDelaunay(a);
}
