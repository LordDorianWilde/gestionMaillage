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
    sommets.last().setIndex(sommets.length() - 1);
}

void Maillage::addTriangle(Triangle t)
{
    triangles.push_back(t);
    triangles.last().setIndex(triangles.length() - 1);
}

int Maillage::sizeTriangles()
{
    return triangles.size();
}

void Maillage::addSommetMaillage(Sommet s)
{
    addSommet(s);
    s = sommets.last();

    int i = 0 ;
    while(i< triangles.length() && !sommetInTriangle(s, triangles[i]))
    {
        i++;
    }

    if(i < triangles.length())
    {
        Triangle t = triangles[i];
        addSommetInTriangle(s, t);
    }
    else
    {
        addSommetExterieur(s);
    }
}

bool Maillage::sommetInTriangle(Sommet s, Triangle t)
{
    Sommet a = t.getSommet(0);
    Sommet b = t.getSommet(1);
    Sommet c = t.getSommet(2);

    if(isDirect(s, a, b) && isDirect(s, b, c) && isDirect(s, c, a))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Maillage::isDirect(Sommet a, Sommet b, Sommet c)
{
    float xab = b.getCoordonne(0) - a.getCoordonne(0);
    float xac = c.getCoordonne(0) - a.getCoordonne(0);
    float yab = b.getCoordonne(1) - a.getCoordonne(1);
    float yac = c.getCoordonne(1) - a.getCoordonne(1);

    float z = xab*yac - yab*xac;
    return (z > 0.0);
}

void Maillage::addSommetInTriangle(Sommet s, Triangle t)
{
    Sommet a = t.getSommet(0);
    Sommet b = t.getSommet(1);
    Sommet c = t.getSommet(2);

    Triangle t1 = Triangle(this, s.getIndex(), c.getIndex(), a.getIndex());
    Triangle t2 = Triangle(this, s.getIndex(), a.getIndex(), b.getIndex());


    this->addTriangle(t1);
    this->addTriangle(t2);
    Triangle* pt1 = getTriangle(triangles.length()-2);
    Triangle* pt2 = getTriangle(triangles.length()-1);
    Triangle* pt = getTriangle(t.getIndex());
    pt->setSommet(0, s.getIndex());

    int Indexb = -1;
    int Indexc = -1;
    Triangle* tb;
    Triangle* tc;

    if(t.getNumberTriangle(1) != -1)
    {
        tb = getTriangle(pt->getTriangle(1).getIndex());
        Indexb = tb->getIndex();
        int tbi = tb->getIndexTriangle(pt->getIndex());
        tb->setTriangle(tbi, pt1->getIndex());
        pt1->setTriangle(0, Indexb);
    }
    else
    {
        pt1->setTriangle(0, -1);
    }

    if(t.getNumberTriangle(2) != -1)
    {
        tc = getTriangle(pt->getTriangle(2).getIndex());
        Indexc = tc->getIndex();
        int tci = tc->getIndexTriangle(pt->getIndex());
        tc->setTriangle(tci, pt2->getIndex());
        pt2->setTriangle(0, Indexc);
    }
    else
    {
        pt2->setTriangle(0, -1);
    }


    pt1->setTriangle(1, pt2->getIndex());
    pt1->setTriangle(2, t.getIndex());

    pt2->setTriangle(1, t.getIndex());
    pt2->setTriangle(2, pt1->getIndex());

    pt->setTriangle(1, pt1->getIndex());
    pt->setTriangle(2, pt2->getIndex());
}

void Maillage::addSommetExterieur(Sommet s)
{

}
