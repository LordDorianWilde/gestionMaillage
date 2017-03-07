#include "gasket.h"
#include <cstdlib>
#include <GL/gl.h>


Gasket::Gasket()
{
    maillage = Maillage();
    generator = default_random_engine();
}

void Gasket::parseFichier(QString filename)
{
    ParserOff p = ParserOff();
    maillage.clear();
    p.parseFichier(maillage, filename);
}

void Gasket::addPoint(double x, double y)
{
    Sommet s = Sommet(x, y, 0);
    maillage.addSommetMaillage(s);
}

void Gasket::addPoint(double xmin, double xmax, double ymin, double ymax, int number)
{
    maillage.clear();
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

        QVector<int> aux = maillage.getTriangle(i)->sommets;
        int aa = aux[0];
        int bb = aux[1];
        int cc = aux[2];
        int a = (*maillage.getSommet(aa)).index;
        double a1 = (*maillage.getSommet(aa)).coordonnees[0];
        double a2 = (*maillage.getSommet(aa)).coordonnees[1];
        int b = (*maillage.getSommet(bb)).index;
        double b1 = (*maillage.getSommet(bb)).coordonnees[0];
        double b2 = (*maillage.getSommet(bb)).coordonnees[1];
        int c = (*maillage.getSommet(cc)).index;
        double c1 = (*maillage.getSommet(cc)).coordonnees[0];
        double c2 = (*maillage.getSommet(cc)).coordonnees[1];

        if(a == 0 || b == 0 || c == 0)
        {
            continue;
        }

        glVertex2f((a1 - x)*zoom, (a2 - y)*zoom);
        glVertex2f((b1 - x)*zoom, (b2 - y)*zoom);

        glVertex2f((b1 - x)*zoom, (b2 - y)*zoom);
        glVertex2f((c1 - x)*zoom, (c2 - y)*zoom);

        glVertex2f((c1 - x)*zoom, (c2 - y)*zoom);
        glVertex2f((a1 - x)*zoom, (a2 - y)*zoom);

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
    maillage.clear();
}

void Gasket::optimize()
{
    maillage.Delaunay();
}

void Gasket::crust()
{
    maillage.crust();
}

void Gasket::incDelaunay(bool a)
{
    maillage.setDelaunayInc(a);
}
