#ifndef SOMMET_H
#define SOMMET_H
#include "maillage.h"
#include "triangle.h"

using namespace std;
class Maillage;
class Triangle;

class Sommet
{
    private:
        Maillage* maillage;
        int triangle;
        int index;
        float coordonnees[3];
    public:
        Sommet();
        Sommet(Maillage*, float, float, float);
        Sommet(Maillage*, float, float, float, int);
        float getCoordonne(int);
        void setTriangle(int);
        int getIndex();
        void setIndex(int);
        int getTriangle();
};

#endif // SOMMET_H
