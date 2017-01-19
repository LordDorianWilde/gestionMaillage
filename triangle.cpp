#include "triangle.h"

Triangle::Triangle(Maillage* m, int a, int b, int c)
{
    sommets[0] = a;
    sommets[1] = b;
    sommets[2] = c;
    maillage = m;
    index = m->sizeTriangles();

    triangles[0] = -1;
    triangles[1] = -1;
    triangles[2] = -1;
}

Triangle::Triangle()
{
    sommets[0] = 0;
    sommets[1] = 0;
    sommets[2] = 0;
    maillage = NULL;

    triangles[0] = 0;
    triangles[1] = 0;
    triangles[2] = 0;
}

Triangle::Triangle(Maillage* m, int a, int b, int c, int d, int e, int f)
{
    sommets[0] = a;
    sommets[1] = b;
    sommets[2] = c;
    maillage = m;
    index = m->sizeTriangles();

    triangles[0] = d;
    triangles[1] = e;
    triangles[2] = f;
}

Triangle Triangle::getTriangle(int i)
{
    i = i%3;
    return *(maillage->getTriangle(triangles[i]));
}

Sommet Triangle::getSommet(int i)
{
    i = i%3;
    return *(maillage->getSommet(sommets[i]));
}

void Triangle::setTriangle(int i, int t)
{
    i = i%3;
    triangles[i] = t;
}

int Triangle::indexOtherSommet(int a, int b)
{
    for(int i = 0; i<3; i++)
    {
        if(sommets[i] != a && sommets[i] != b)
        {
            return i;
        }
    }
}

int Triangle::getNumberSommet(int i)
{
    i = i%3;
    return sommets[i];
}

int Triangle::getNumberTriangle(int i)
{
    i = i%3;
    return triangles[i];
}

int Triangle::getIndex()
{
    return index;
}

int Triangle::getIndexTriangle(int t)
{
    for(int i=0; i<3; i++)
    {
        if(triangles[i] == t)
            return i;
    }
    return -1;
}

int Triangle::getIndexSommet(int s)
{
    for(int i=0; i<3; i++)
    {
        if(sommets[i] == s)
            return i;
    }
    return -1;
}

