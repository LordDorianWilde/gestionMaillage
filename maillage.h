#ifndef MAILLAGE_H
#define MAILLAGE_H
#include <QVector>
#include "sommet.h"
#include "triangle.h"

using namespace std;
class Maillage
{

    private:
        QVector<Sommet> sommets;
        QVector<Triangle> triangles;

    public:
        Maillage();
        Sommet* getSommet(int);
        Triangle* getTriangle(int);
        void addSommet(Sommet);
        void addTriangle(Triangle);
        int sizeTriangles();
};

#endif // MAILLAGE_H
