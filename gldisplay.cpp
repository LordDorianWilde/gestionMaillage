#include "gldisplay.h"

GLDisplay::GLDisplay(QWidget *parent) :
    QGLWidget(parent)
{
    mousePressed = false;
    translateX = 0.0;
    translateY = 0.0;
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
    gasket.draw();

    update();

}

void GLDisplay::parse(QString filename)
{
    gasket.parseFichier(filename);
}

void GLDisplay::addPoint(float x, float y)
{
    gasket.addPoint(x, y);
}

void GLDisplay::clear()
{
    gasket.clear();
}

void GLDisplay::optimize()
{
    gasket.optimize();
}

void GLDisplay::randomPoints(float xmin, float xmax, float ymin, float ymax, int number)
{
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distributionX(xmin, xmax);
    std::uniform_real_distribution<float> distributionY(ymin, ymax);

    for(int i = 0; i<number; i++)
    {
        float x = distributionX(generator);
        float y = distributionY(generator);

        addPoint(x, y);
    }
}

void GLDisplay::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void GLDisplay::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
    mousePressed = true;
}

void GLDisplay::mouseMoveEvent(QMouseEvent *event)
{
    if(mousePressed)
    {
        float a = (event->pos().x() - lastPos.x()) * 2;
        float b = (event->pos().y() - lastPos.y()) * 2;
        float w = (this->width());
        float h = (this->height());
        float x = a / w;
        float y = b / h;
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
