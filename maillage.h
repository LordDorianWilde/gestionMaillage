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
        void addSommetMaillage(Sommet);
        bool sommetInTriangle(Sommet, Triangle);
        bool isDirect(Sommet, Sommet, Sommet);
        void addSommetInTriangle(Sommet, Triangle);
        void addSommetExterieur(Sommet);
};

#endif // MAILLAGE_H
