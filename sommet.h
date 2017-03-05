#ifndef SOMMET_H
#define SOMMET_H
#include "triangle.h"

using namespace std;
class Maillage;
class Triangle;

class Sommet
{
    public:
        int triangle;
        int index;
        float coordonnees[3];
        Sommet();
        Sommet(float, float, float);
        Sommet(float, float, float, int);
};

#endif // SOMMET_H
