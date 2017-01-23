#include <iostream>
#include <QDebug>
#include "parseroff.h"

using namespace std;

int main()
{
    ParserOff p = ParserOff();
    Maillage m = p.parseFichier("queen.off");

    Sommet s = Sommet(&m, 0.75, 0.75, 0);
    m.addSommetMaillage(s);

    return 0;
}

