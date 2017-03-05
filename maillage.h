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
        int sommetInTriangle(Sommet, int i);
        bool isDirect(Sommet, Sommet, Sommet);
        void addSommetInTriangle(Sommet, Triangle);
        void addSommetExterieur(int);
        void flipArete(int indexT, int indexS, int indexU);
        void flipInfini(int sommet);
        int nextTriangleRotating(int sommet, int triangle, int sens);
};

#endif // MAILLAGE_H
