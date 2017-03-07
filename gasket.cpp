#include "gasket.h"
#include <cstdlib>
#include <time.h>
#include <GL/gl.h>


Gasket::Gasket()
{
    maillage = Maillage();
    generator = default_random_engine();
}

void Gasket::parseFichier(QString filename)
{
    ParserOff p = ParserOff();
    maillage = p.parseFichier(filename);
    maillage.Delaunay();
}

void Gasket::addPoint(double x, double y)
{
    Sommet s = Sommet(x, y, 0);
    maillage.addSommetMaillage(s);
}

void Gasket::addPoint(double xmin, double xmax, double ymin, double ymax, int number)
{
    std::uniform_real_distribution<double> distributionX(xmin, xmax);
    std::uniform_real_distribution<double> distributionY(ymin, ymax);
    maillage.addSizeSommet(number);
    maillage.addSizeTriangle(2*number);

    for(int i = 0; i<number; i++)
    {
        double x = distributionX(generator);
        double y = distributionY(generator);

        Sommet s = Sommet(x, y, 0);
        maillage.addSommetMaillage(s);
    }
}

void Gasket::draw()
{
    double x = translateX;
    double y = translateY;
    glBegin(GL_LINES);

    glColor3f(0.0f, 0.0f, 0.0f);

    for( int i = 0; i < maillage.sizeTriangles(); i++ ) {

        Sommet a = (*maillage.getSommet(maillage.getTriangle(i)->sommets[0]));
        Sommet b = (*maillage.getSommet(maillage.getTriangle(i)->sommets[1]));
        Sommet c = (*maillage.getSommet(maillage.getTriangle(i)->sommets[2]));

        if(a.index == 0 || b.index == 0 || c.index == 0)
        {
            continue;
        }

        glVertex2f((a.coordonnees[0] - x)*zoom, (a.coordonnees[1] - y)*zoom);
        glVertex2f((b.coordonnees[0] - x)*zoom, (b.coordonnees[1] - y)*zoom);

        glVertex2f((b.coordonnees[0] - x)*zoom, (b.coordonnees[1] - y)*zoom);
        glVertex2f((c.coordonnees[0] - x)*zoom, (c.coordonnees[1] - y)*zoom);

        glVertex2f((c.coordonnees[0] - x)*zoom, (c.coordonnees[1] - y)*zoom);
        glVertex2f((a.coordonnees[0] - x)*zoom, (a.coordonnees[1] - y)*zoom);

    }

    //draw crust in red
    glColor3f(1.0f, 0.0f, 0.0f);
    for( int i = 0; i < maillage.sizeBord(); i++ ) {
        pair<int, int>* p = maillage.getBord(i);


        Sommet a = (*maillage.getSommet(p->first));
        Sommet b = (*maillage.getSommet(p->second));

        if(a.index == 0 || b.index == 0)
        {
            continue;
        }

        glVertex2f((a.coordonnees[0] - x)*zoom, (a.coordonnees[1] - y)*zoom);
        glVertex2f((b.coordonnees[0] - x)*zoom, (b.coordonnees[1] - y)*zoom);

    }

    glEnd();

}

void Gasket::clear()
{
    maillage = Maillage();
}

void Gasket::optimize()
{
    maillage.Delaunay();
}

void Gasket::crust() {
    maillage.crust();
}

void Gasket::incDelaunay(bool a)
{
    maillage.setDelaunayInc(a);
}
