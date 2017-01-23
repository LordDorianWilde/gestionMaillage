#include "sommet.h"

Sommet::Sommet(Maillage* m, float a, float b, float c)
{
    coordonnees[0] = a;
    coordonnees[1] = b;
    coordonnees[2] = c;
    maillage = m;
    index = -1;
    triangle = -1;
}
Sommet::Sommet()
{
    coordonnees[0] = 0;
    coordonnees[1] = 0;
    coordonnees[2] = 0;
    maillage = NULL;
    index = -1;
    triangle = -1;
}

Sommet::Sommet(Maillage* m, float a, float b, float c, int t)
{
    coordonnees[0] = a;
    coordonnees[1] = b;
    coordonnees[2] = c;
    index = -1;
    maillage = m;
    triangle = t;
}

void Sommet::setTriangle(int a)
{
    triangle = a;
}

float Sommet::getCoordonne(int i)
{
    i = i%3;
    return coordonnees[i];
}

int Sommet::getTriangle()
{
    return triangle;
}

int Sommet::getIndex()
{
    return index;
}

void Sommet::setIndex(int a)
{
    index = a;
}
