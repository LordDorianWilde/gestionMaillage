#include "maillage.h"
#include <ctime>

Maillage::Maillage()
{
    sommets = QVector<Sommet>();
    triangles = QVector<Triangle>();
    indexSommet = 0;
    indexTriangle = 0;
    nbVoronoiCenter = 0;
    delaunayInc = false;
    bord = QVector<pair<int,int>>();;
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
    if(indexSommet < sommets.size())
    {
        sommets[indexSommet] = s;
        sommets[indexSommet].index = indexSommet;
        indexSommet++;
    }
    else
    {
        sommets.push_back(s);
        sommets.last().index = indexSommet;
        indexSommet++;
    }
}

void Maillage::addTriangle(Triangle t)
{
    if(indexTriangle < triangles.size())
    {
        triangles[indexTriangle] = t;
        triangles[indexTriangle].index = indexTriangle;
        indexTriangle++;
    }
    else
    {
        triangles.push_back(t);
        triangles.last().index = indexTriangle;
        indexTriangle++;
    }
}

int Maillage::sizeTriangles()
{
    return triangles.size();
}

int Maillage::sizeSommets()
{
    return sommets.size();
}

void Maillage::addSizeSommet(int s)
{
    indexSommet = sommets.size();
    sommets.resize(indexSommet + s);
}

void Maillage::addSizeTriangle(int s)
{
    indexTriangle = triangles.size();
    triangles.resize(indexTriangle - 2 + s);
}

void Maillage::addSommetMaillage(Sommet s)
{
    addSommet(s);
    s = sommets[indexSommet-1];

    if(indexSommet > 4)
    {
        int i = 0 ;
        int next = sommetInTriangle(s, i);
        while(i != next)
        {
            i = next;
            next = sommetInTriangle(s, i);
        }

        sommets[indexSommet-1].triangle = i;
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
        if(delaunayInc)
            Delaunay(indexSommet - 1);
    }
    else if(indexSommet == 4)
    {
        if(isDirect(sommets[1],sommets[2],sommets[3]))
        {
            Triangle t = Triangle(1,2,3,2,3,1);
            Triangle t1 = Triangle(0,2,1,0,3,2);
            Triangle t2 = Triangle(0,3,2,0,1,3);
            Triangle t3 = Triangle(0,1,3,0,2,1);
            sommets[1].triangle = 0;
            sommets[2].triangle = 0;
            sommets[3].triangle = 0;
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
            sommets[1].triangle = 0;
            sommets[2].triangle = 0;
            sommets[3].triangle = 0;
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

    if(!isDirect(s, a, b))
    {
        return t.triangles[2];
    }
    else if(!isDirect(s, b, c))
    {
        return t.triangles[0];
    }
    else if(!isDirect(s, c, a))
    {
        return t.triangles[1];
    }
    else
    {
        return i;
    }
}

bool Maillage::isDirect(Sommet a, Sommet b, Sommet c)
{
    if(a.index == 0 || b.index == 0 || c.index == 0)
        return true;

    double xab = b.coordonnees[0] - a.coordonnees[0];
    double xac = c.coordonnees[0] - a.coordonnees[0];
    double yab = b.coordonnees[1] - a.coordonnees[1];
    double yac = c.coordonnees[1] - a.coordonnees[1];

    double z = xab*yac - yab*xac;
    return (z >= 0.0);
}

void Maillage::addSommetInTriangle(Sommet s, Triangle t)
{
    Sommet a = sommets[t.sommets[0]];
    Sommet b = sommets[t.sommets[1]];
    Sommet c = sommets[t.sommets[2]];

    Triangle t1 = Triangle(s.index, c.index, a.index);
    Triangle t2 = Triangle(s.index, a.index, b.index);


    addTriangle(t1);
    int indexMaillageT1 = indexTriangle-1;
    addTriangle(t2);
    int indexMaillageT2 = indexTriangle-1;
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

double Maillage::toFlip(int t, int a, int u)
{
    int indexAT = triangles[t].sommets.indexOf(a);
    int b = triangles[t].sommets[(indexAT+1)%3];
    int c = triangles[t].sommets[(indexAT+2)%3];
    int d = triangles[u].sommets[triangles[u].indexOtherSommet(b, c)];

    Matrix4d m(4,4);

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

    double det = m.determinant();

    return det;
}

void Maillage::Delaunay()
{
    set<int> toProcess = set<int>();
    for(int i = 0; i < triangles.size(); i++)
    {
        for(int j = 0; j<3; j++)
        {
            if(i < triangles[i].triangles[j] &&
                    triangles[i].sommets[0] != 0 && triangles[i].sommets[1] != 0 && triangles[i].sommets[2] != 0 &&
                    triangles[triangles[i].triangles[j]].sommets[0] != 0 && triangles[triangles[i].triangles[j]].sommets[1] != 0 && triangles[triangles[i].triangles[j]].sommets[2] != 0)
            {  
                if(toFlip(i, triangles[i].sommets[j], triangles[i].triangles[j]) > 1e-13)
                {
                    flipArete(i, triangles[i].sommets[j], triangles[i].triangles[j]);

                    for(int k = 0; k<3; k++)
                    {
                        toProcess.insert(triangles[i].triangles[k]);
                    }

                    for(int k = 0; k<3; k++)
                    {
                        toProcess.insert(triangles[triangles[i].triangles[j]].triangles[k]);
                    }
                }
            }
        }
    }

    while(!toProcess.empty())
    {
        int i = *(toProcess.begin());
        for(int j = 0; j<3; j++)
        {
            if(triangles[i].sommets[0] != 0 && triangles[i].sommets[1] != 0 && triangles[i].sommets[2] != 0 &&
                    triangles[triangles[i].triangles[j]].sommets[0] != 0 && triangles[triangles[i].triangles[j]].sommets[1] != 0 && triangles[triangles[i].triangles[j]].sommets[2] != 0)
            {
                if(toFlip(i, triangles[i].sommets[j], triangles[i].triangles[j]) > 1e-13)
                {
                    flipArete(i, triangles[i].sommets[j], triangles[i].triangles[j]);

                    for(int k = 0; k<3; k++)
                    {
                        toProcess.insert(triangles[i].triangles[k]);
                    }

                    for(int k = 0; k<3; k++)
                    {
                        toProcess.insert(triangles[triangles[i].triangles[j]].triangles[k]);
                    }
                }
            }
        }
        toProcess.erase(i);
    }

    qDebug() << "fini !" << endl;
}

void Maillage::Delaunay(int i)
{
    int t = sommets[i].triangle;
    set<int> toProcess = set<int>({t});

    while(toProcess.find(nextTriangleRotating(i,t,1)) == toProcess.end())
    {
        t = nextTriangleRotating(i,t,1);
        toProcess.insert(t);
    }

    while(!toProcess.empty())
    {
        int i = *(toProcess.begin());
        for(int j = 0; j<3; j++)
        {
            if(triangles[i].sommets[0] != 0 && triangles[i].sommets[1] != 0 && triangles[i].sommets[2] != 0 &&
                    triangles[triangles[i].triangles[j]].sommets[0] != 0 && triangles[triangles[i].triangles[j]].sommets[1] != 0 && triangles[triangles[i].triangles[j]].sommets[2] != 0)
            {
                if(toFlip(i, triangles[i].sommets[j], triangles[i].triangles[j]) > 1e-13)
                {
                    flipArete(i, triangles[i].sommets[j], triangles[i].triangles[j]);

                    for(int k = 0; k<3; k++)
                    {
                        toProcess.insert(triangles[i].triangles[k]);
                    }

                    for(int k = 0; k<3; k++)
                    {
                        toProcess.insert(triangles[triangles[i].triangles[j]].triangles[k]);
                    }
                }
            }
        }
        toProcess.erase(i);
    }

    qDebug() << "fini !" << endl;
}

Sommet Maillage::getVoronoiCenter(int s1, int s2, int s3) {

    //circumcenter coordinates found on Wolfram site : http://mathworld.wolfram.com/Circumcircle.html

    double Ax = sommets[s1].coordonnees[0];
    double Ay = sommets[s1].coordonnees[1];
    double Bx = sommets[s2].coordonnees[0];
    double By = sommets[s2].coordonnees[1];
    double Cx = sommets[s3].coordonnees[0];
    double Cy = sommets[s3].coordonnees[1];

    double nA = Ax*Ax+Ay*Ay;
    double nB = Bx*Bx+By*By;
    double nC = Cx*Cx+Cy*Cy;

    Matrix3d m(3,3);

    m(0,0) = Ax;
    m(0,1) = Ay;
    m(0,2) = 1;
    m(1,0) = Bx;
    m(1,1) = By;
    m(1,2) = 1;
    m(2,0) = Cx;
    m(2,1) = Cy;
    m(2,2) = 1;
    double a = m.determinant();

    m(0,0) = nA;
    m(1,0) = nB;
    m(2,0) = nC;
    double bx = -m.determinant();


    m(0,1) = Ax;
    m(1,1) = Bx;
    m(2,1) = Cx;
    double by = m.determinant();

    double x0 = -bx/(2*a);
    double y0 = -by/(2*a);

    Sommet S (x0,y0, 0);
    return S;
}

Sommet Maillage::getVoronoiCenter(int t) {
    int s1 = triangles[t].sommets[0];
    int s2 = triangles[t].sommets[1];
    int s3 = triangles[t].sommets[2];
    return this->getVoronoiCenter(s1, s2, s3);
}

void Maillage::crust() {
    // calculer tous les centres de voronoi
    // stocker le nombre de points de voronoi
    // ajouter au maillage
    // delaunay bruteforce
    // filter les arretes : garder uniquement celles avec des points d'origines
    // attention à pas donner deux fois la même arrete

    this->Delaunay();

    QVector<Sommet> temp(this->triangles.size());

    int i;
    nbVoronoiCenter = 0;
    for (i = 0; i < triangles.size(); ++i) {
        if (!isTriangleInfinite(i)) {
            Sommet s = this->getVoronoiCenter(i);
            temp[nbVoronoiCenter] = s;
            nbVoronoiCenter++;
        }
    }
    for (i = 0; i < nbVoronoiCenter; ++i) {
        this->addSommetMaillage(temp[i]);
    }
    this->Delaunay();

    bord.clear();
    bord.resize(3*triangles.size());

    int a, b, c, nbBords = 0;
    int nbOriginal = sommets.size()-nbVoronoiCenter;
    for (i = 0; i < triangles.size(); ++i) {
        a = triangles[i].sommets[0];
        b = triangles[i].sommets[1];
        c = triangles[i].sommets[2];
        if (a != 0 && b!=0 && a < nbOriginal && b < nbOriginal ) {
            pair<int, int> p (a,b);
            bord[nbBords] = p;
            nbBords++;
        }
        if (a != 0 && c!=0 && a < nbOriginal && c < nbOriginal ) {
            pair<int, int> p (a,c);
            bord[nbBords] = p;
            nbBords++;
        }
        if (b != 0 && c!=0 && b < nbOriginal && c < nbOriginal ) {
            pair<int, int> p (b,c);
            bord[nbBords] = p;
            nbBords++;
        }
    }
    bord.resize(nbBords);

}

bool Maillage::isTriangleInfinite(int t) {
    return this->triangles[t].sommets[0] == 0 || this->triangles[t].sommets[1] == 0 || this->triangles[t].sommets[2] == 0;
}

int Maillage::sizeBord() {
    return bord.size();
}

pair<int, int> *Maillage::getBord(int i) {
    return &bord[i];
}

void Maillage::setDelaunayInc(bool a)
{
    delaunayInc = a;
}
