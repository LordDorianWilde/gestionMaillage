#include "maillage.h"

Maillage::Maillage()
{
    sommets = QVector<Sommet>();
    triangles = QVector<Triangle>();

    Sommet infinie(0, 0, 0);
    addSommet(infinie);
}

Sommet *Maillage::getSommet(int i)
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
    sommets.last().index = sommets.length() - 1;
}

void Maillage::addTriangle(Triangle t)
{
    triangles.push_back(t);
    triangles.last().index = triangles.length() - 1;
}

int Maillage::sizeTriangles()
{
    return triangles.size();
}

void Maillage::addSommetMaillage(Sommet s)
{
    addSommet(s);
    s = sommets.last();

    if(sommets.size() > 4)
    {
        int i = 0 ;
        while(i != -1 && i != sommetInTriangle(s, i))
        {
            i = sommetInTriangle(s, i);
        }

        if(triangles[i].sommets[0] != 0 && triangles[i].sommets[1] != 0 && triangles[i].sommets[2] != 0)
        {
            Triangle t = triangles[i];
            addSommetInTriangle(s, t);
        }
        else
        {
            Triangle t = triangles[i];
            addSommetInTriangle(s, t);
            addSommetExterieur(s.index);
        }
    }
    else if(sommets.size() == 4)
    {
        if(isDirect(sommets[1],sommets[2],sommets[3]))
        {
            Triangle t = Triangle(1,2,3,1,2,3);
            Triangle t1 = Triangle(0,2,1,0,2,1);
            Triangle t2 = Triangle(0,3,2,0,3,2);
            Triangle t3 = Triangle(0,1,3,0,1,3);
            addTriangle(t);
            addTriangle(t1);
            addTriangle(t2);
            addTriangle(t3);
        }
        else
        {
            Triangle t = Triangle(1,3,2,2,1,3);
            Triangle t1 = Triangle(0,1,2,0,2,3);
            Triangle t2 = Triangle(0,2,3,0,3,1);
            Triangle t3 = Triangle(0,3,1,0,1,2);
            addTriangle(t);
            addTriangle(t1);
            addTriangle(t2);
            addTriangle(t3);
        }
    }
}

int Maillage::sommetInTriangle(Sommet s, int i)
{
    Triangle t = triangles[i];
    Sommet a = sommets[t.sommets[0]];
    Sommet b = sommets[t.sommets[1]];
    Sommet c = sommets[t.sommets[2]];

    bool g = isDirect(s, a, b);
    bool f = isDirect(s, b, c);
    bool h = isDirect(s, c, a);

    if(isDirect(s, a, b) && isDirect(s, b, c) && isDirect(s, c, a))
    {
        return i;
    }
    else
    {
        if(!isDirect(s, a, b))
        {
            return t.triangles[2];
        }
        else if(!isDirect(s, b, c))
        {
            return t.triangles[0];
        }
        else
        {
            return t.triangles[1];
        }
    }
}

bool Maillage::isDirect(Sommet a, Sommet b, Sommet c)
{
    float xab = b.coordonnees[0] - a.coordonnees[0];
    float xac = c.coordonnees[0] - a.coordonnees[0];
    float yab = b.coordonnees[1] - a.coordonnees[1];
    float yac = c.coordonnees[1] - a.coordonnees[1];

    if(a.index == 0 || b.index == 0 || c.index == 0)
        return true;

    float z = xab*yac - yab*xac;
    return (z > 0.0);
}

void Maillage::addSommetInTriangle(Sommet s, Triangle t)
{
    Sommet a = sommets[t.sommets[0]];
    Sommet b = sommets[t.sommets[1]];
    Sommet c = sommets[t.sommets[2]];

    Triangle t1 = Triangle(s.index, c.index, a.index);
    Triangle t2 = Triangle(s.index, a.index, b.index);


    addTriangle(t1);
    int indexMaillageT1 = triangles.length()-1;
    addTriangle(t2);
    int indexMaillageT2 = triangles.length()-1;
    int indexMaillageT = t.index;
    triangles[indexMaillageT].sommets[0] = s.index;

    int tb;
    int tc;

    if(t.triangles[1] != -1)
    {
        tb = triangles[indexMaillageT].triangles[1];
        int tbi = triangles[tb].triangles.indexOf(indexMaillageT);
        triangles[tb].triangles[tbi] = indexMaillageT1;
        triangles[indexMaillageT1].triangles[0] = tb;
    }
    else
    {
        triangles[indexMaillageT1].triangles[0] = -1;
    }

    if(t.triangles[2] != -1)
    {
        tc = triangles[indexMaillageT].triangles[2];
        int tci = triangles[tc].triangles.indexOf(indexMaillageT);
        triangles[tc].triangles[tci] = indexMaillageT2;
        triangles[indexMaillageT2].triangles[0] = tc;
    }
    else
    {
        triangles[indexMaillageT2].triangles[0] = -1;
    }


    triangles[indexMaillageT1].triangles[1] = indexMaillageT2;
    triangles[indexMaillageT1].triangles[2] = indexMaillageT;

    triangles[indexMaillageT2].triangles[1] = indexMaillageT;
    triangles[indexMaillageT2].triangles[2] = indexMaillageT1;

    triangles[indexMaillageT].triangles[1] = indexMaillageT1;
    triangles[indexMaillageT].triangles[2] = indexMaillageT2;

    sommets[s.index].triangle = indexMaillageT;
}

void Maillage::addSommetExterieur(int s)
{
    Triangle t = triangles[sommets[s].triangle];

    while(t.sommets[0] == 0 || t.sommets[1] ==0 || t.sommets[2] == 0)
    {
        t = triangles[nextTriangleRotating(s, t.index, 1)];
    }

    int t1 = nextTriangleRotating(s, t.index, 1);
    int t2 = nextTriangleRotating(0, t1, 1);

    while(t2 == sommetInTriangle(sommets[s], t2))
    {
        flipArete(t1, s, t2);

        Triangle aux = triangles[t1];
        if(aux.sommets[0] == 0 || aux.sommets[1] == 0 || aux.sommets[2] == 0)
        {
            t2 = nextTriangleRotating(0, t1, 1);
        }
        else
        {
            t1 = t2;
            t2 = nextTriangleRotating(0, t1, 1);
        }
    }

    t1 = nextTriangleRotating(s, t.index, -1);
    t2 = nextTriangleRotating(0, t1, -1);

    while(t2 == sommetInTriangle(sommets[s], t2))
    {
        flipArete(t1, s, t2);

        Triangle aux = triangles[t1];
        if(aux.sommets[0] == 0 || aux.sommets[1] == 0 || aux.sommets[2] == 0)
        {
            t2 = nextTriangleRotating(0, t1, -1);
        }
        else
        {
            t1 = t2;
            t2 = nextTriangleRotating(0, t1, -1);
        }
    }
}

void Maillage::flipArete(int indexT, int indexS, int indexU)
{
    int sa = triangles[indexT].sommets[(triangles[indexT].sommets.indexOf(indexS)+1)%3];
    int sb = triangles[indexT].sommets[(triangles[indexT].sommets.indexOf(indexS)+2)%3];
    int st = triangles[indexT].sommets[triangles[indexT].indexOtherSommet(sa, sb)];
    int su = triangles[indexU].sommets[triangles[indexU].indexOtherSommet(sa, sb)];

    int t_tb = triangles[indexT].triangles[triangles[indexT].sommets.indexOf(sa)];
    int t_ta = triangles[indexT].triangles[triangles[indexT].sommets.indexOf(sb)];
    int t_ub = triangles[indexU].triangles[triangles[indexU].sommets.indexOf(sa)];
    int t_ua = triangles[indexU].triangles[triangles[indexU].sommets.indexOf(sb)];

    triangles[indexT].sommets[0] = sb;
    triangles[indexT].sommets[1] = st;
    triangles[indexT].sommets[2] = su;

    triangles[indexT].triangles[0] = indexU;
    triangles[indexT].triangles[1] = t_ub;
    triangles[indexT].triangles[2] = t_tb;

    if(t_ub >= 0)
        triangles[t_ub].triangles[triangles[t_ub].triangles.indexOf(indexU)] = indexT;

    triangles[indexU].sommets[0] = sa;
    triangles[indexU].sommets[1] = su;
    triangles[indexU].sommets[2] = st;

    triangles[indexU].triangles[0] = indexT;
    triangles[indexU].triangles[1] = t_ta;
    triangles[indexU].triangles[2] = t_ua;

    if(t_ta >= 0)
        triangles[t_ta].triangles[triangles[t_ta].triangles.indexOf(indexT)] = indexU;
}

int Maillage::nextTriangleRotating(int sommet, int triangle, int sens)
{
    int indexSommet = ((triangles[triangle].sommets.indexOf(sommet) + sens) + 3)%3;
    int reponse = triangles[triangle].triangles[indexSommet];
    return reponse;
}

bool Maillage::toFlip(int t, int a, int u)
{
    int indexAT = triangles[t].sommets.indexOf(a);
    int b = triangles[t].sommets[(indexAT+1)%3];
    int c = triangles[t].sommets[(indexAT+2)%3];
    int d = triangles[u].sommets[triangles[u].indexOtherSommet(b, c)];

    Matrix4f m(4,4);

    m(0,0) = sommets[a].coordonnees[0];
    m(0,1) = sommets[a].coordonnees[1];
    m(0,2) = m(0,0)*m(0,0) + m(0,1)*m(0,1);
    m(0,3) = 1;

    m(1,0) = sommets[b].coordonnees[0];
    m(1,1) = sommets[b].coordonnees[1];
    m(1,2) = m(1,0)*m(1,0) + m(1,1)*m(1,1);
    m(1,3) = 1;

    m(2,0) = sommets[c].coordonnees[0];
    m(2,1) = sommets[c].coordonnees[1];
    m(2,2) = m(2,0)*m(2,0) + m(2,1)*m(2,1);
    m(2,3) = 1;

    m(3,0) = sommets[d].coordonnees[0];
    m(3,1) = sommets[d].coordonnees[1];
    m(3,2) = m(3,0)*m(3,0) + m(3,1)*m(3,1);
    m(3,3) = 1;

    float det = m.determinant();

    return det > 0;
}

void Maillage::Delaunay()
{
    bool finish = false;
    int i = 0;
    while(!finish || i < triangles.size())
    {
        if(i==0)
            finish = true;

        for(int j = 0; j<3; j++)
        {
            if(i < triangles[i].triangles[j] &&
                    triangles[i].sommets[0] != 0 && triangles[i].sommets[1] != 0 && triangles[i].sommets[2] != 0 &&
                    triangles[triangles[i].triangles[j]].sommets[0] != 0 && triangles[triangles[i].triangles[j]].sommets[1] != 0 && triangles[triangles[i].triangles[j]].sommets[2] != 0)
            {
                if(toFlip(i, triangles[i].sommets[j], triangles[i].triangles[j]))
                {
                    finish = false;
                    flipArete(i, triangles[i].sommets[j], triangles[i].triangles[j]);
                }
            }
        }
        i++;

        if(i == triangles.size() && !finish)
            i = 0;
    }
}
