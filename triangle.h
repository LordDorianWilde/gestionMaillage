#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "sommet.h"
#include <QVector>

using namespace std;
class Sommet;

class Triangle
{
public:
    int index;
    QVector<int> triangles;
    QVector<int> sommets;
    Triangle();
    Triangle(int, int, int);
    Triangle(int, int, int, int, int, int);
    int indexOtherSommet(int, int);
};

#endif // TRIANGLE_H
