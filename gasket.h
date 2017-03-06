#ifndef GASKET_H
#define GASKET_H
#include "parseroff.h"
#include <QPoint>
#include <random>


class Gasket
{
public:
    Gasket();
    double translateX;
    double translateY;
    double zoom;
    void draw();
    void parseFichier(QString filename);
    void addPoint(double xmin, double xmax, double ymin, double ymax, int number);
    void addPoint(double x, double y);
    void clear();
    void optimize();

private:
    Maillage maillage;
    std::default_random_engine generator;
};

#endif // GASKET_H
