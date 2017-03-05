#include "gasket.h"
#include <cstdlib>
#include <time.h>
#include <GL/gl.h>


Gasket::Gasket()
{

}

void Gasket::parseFichier(QString filename)
{
    ParserOff p = ParserOff();
    maillage = p.parseFichier(filename);
}

void Gasket::addPoint(float x, float y)
{
    Sommet s = Sommet(x, y, 0);
    maillage.addSommetMaillage(s);
}

void Gasket::draw()
{
    float x = translateX;
    float y = translateY;
    glBegin(GL_LINES);

    for( int i = 0; i < maillage.sizeTriangles(); i++ ) {
        Sommet a = (*maillage.getSommet(maillage.getTriangle(i)->sommets[0]));
        Sommet b = (*maillage.getSommet(maillage.getTriangle(i)->sommets[1]));
        Sommet c = (*maillage.getSommet(maillage.getTriangle(i)->sommets[2]));

        if(a.index == 0 || b.index == 0 || c.index == 0)
        {
            continue;
        }

        glVertex2f(a.coordonnees[0] - x, a.coordonnees[1] - y);
        glVertex2f(b.coordonnees[0] - x, b.coordonnees[1] - y);

        glVertex2f(b.coordonnees[0] - x, b.coordonnees[1] - y);
        glVertex2f(c.coordonnees[0] - x, c.coordonnees[1] - y);

        glVertex2f(c.coordonnees[0] - x, c.coordonnees[1] - y);
        glVertex2f(a.coordonnees[0] - x, a.coordonnees[1] - y);
    }

    glEnd();

}
