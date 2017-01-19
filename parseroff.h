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
    Maillage m;
    map< QPair<int, int>, int> areteTriangle;
public:
    ParserOff();
    Maillage parseFichier(QString);
    void processSommet(float, float, float);
    void processTriangle(int, int, int);
    void linkTriangles(int, int);
};

#endif // PARSEROFF_H
