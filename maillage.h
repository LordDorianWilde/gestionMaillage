#ifndef MAILLAGE_H
#define MAILLAGE_H
#include <QVector>
#include "sommet.h"
#include "triangle.h"
#include "Eigen/Dense"
#include "Eigen/LU"

using namespace std;
using namespace Eigen;

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
        double toFlip(int t, int a, int u);
        void Delaunay();
};

#endif // MAILLAGE_H
