#ifndef GASKET_H
#define GASKET_H
#include "parseroff.h"
#include <QPoint>


class Gasket
{
public:
    Gasket();
    float translateX;
    float translateY;
    void draw();
    void parseFichier(QString filename);
    void addPoint(float x, float y);

private:
    Maillage maillage;
};

#endif // GASKET_H
