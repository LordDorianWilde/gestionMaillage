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
        double coordonnees[3];
        Sommet();
        Sommet(double, double, double);
        Sommet(double, double, double, int);
};

#endif // SOMMET_H
