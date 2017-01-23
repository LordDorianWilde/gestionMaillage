#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "maillage.h"
#include "sommet.h"

using namespace std;
class Maillage;
class Sommet;

class Triangle
{
private:
    int index;
    Maillage* maillage;
    int sommets[3];
    int triangles[3];

public:
    Triangle();
    Triangle(Maillage*, int, int, int);
    Triangle(Maillage*, int, int, int, int, int, int);
    Triangle getTriangle(int);
    int getNumberTriangle(int);
    Sommet getSommet(int);
    void setSommet(int, int);
    int getNumberSommet(int);
    int getIndexTriangle(int);
    int getIndexSommet(int);
    int indexOtherSommet(int, int);
    void setTriangle(int, int);
    int getIndex();
    void setIndex(int);
};

#endif // TRIANGLE_H
