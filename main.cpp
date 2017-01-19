#include <iostream>
#include <QDebug>
#include "parseroff.h"

using namespace std;

int main()
{
    ParserOff p = ParserOff();
    Maillage m = p.parseFichier("queen.off");

    return 0;
}

