#include "maillage.h"

Maillage::Maillage()
{
    sommets = QVector<Sommet>();
    triangles = QVector<Triangle>();
}

Sommet* Maillage::getSommet(int i)
{
    return &sommets[i];
}

Triangle* Maillage::getTriangle(int i)
{
    return &triangles[i];
}

void Maillage::addSommet(Sommet s)
{
    sommets.push_back(s);
}

void Maillage::addTriangle(Triangle t)
{
    triangles.push_back(t);
}

int Maillage::sizeTriangles()
{
    return triangles.size();
}
