#ifndef PARSEROFF_H
#define PARSEROFF_H
#include "maillage.h"
#include <iostream>
#include <string>
#include <QFile>
#include <QTextStream>
#include <fstream>
#include <qpair.h>
#include <map>

using namespace std;
class Maillage;

class ParserOff
{
private:
    map< QPair<int, int>, int> areteTriangle;
public:
    ParserOff();
    void parseFichier(Maillage&, QString);
    void processSommet(Maillage&, double, double, double);
    void processTriangle(Maillage&, int, int, int);
    void linkTriangles(Maillage&, int, int);
};

#endif // PARSEROFF_H
