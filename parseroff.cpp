#include "parseroff.h"
#include <QStringList>

ParserOff::ParserOff()
{
    areteTriangle = map< QPair<int, int>, int>();
}

void ParserOff::parseFichier(Maillage& m, QString fileName)
{
    QFile file (fileName);
    std::cout << "file" << endl;

    QStringList list;
    if (not file.open (QIODevice::ReadOnly | QIODevice::Text)) {
        //sendMessage (tr ("Impossible de lire le fichier %1").arg (fileName));
    }
    QTextStream in (&file);
    in.setCodec ("UTF-8");

    list = in.readAll ().split ('\n', QString::KeepEmptyParts);

    for(int i = 2; i<list.size(); i++)
    {
        QStringList coord = list[i].split(" ",QString::SkipEmptyParts);
        if(coord.size() == 3)
        {
            processSommet(m, coord[0].toDouble(), coord[1].toDouble(), coord[2].toDouble());
        }
        if(coord.size() == 4 && m.getDelaunayInc() == false)
        {
            processTriangle(m, coord[1].toInt() + 1, coord[2].toInt() + 1, coord[3].toInt() + 1);
        }
    }

    map< QPair<int, int>, int>::iterator it(areteTriangle.begin());
    while(areteTriangle.size() > 0)
    {
        QPair<int, int> arete = (*it).first;
        if(arete.second != 0 && arete.first != 0)
        {
            processTriangle(m, 0, arete.second, arete.first);
            it = areteTriangle.begin();
        }
        else
        {
            it++;
        }

    }
}

void ParserOff::processSommet(Maillage& m, double a, double b, double c)
{
    Sommet s = Sommet(a, b, c);
    if(m.getDelaunayInc() == false)
        m.addSommet(s);
    else
        m.addSommetMaillage(s);
}

void ParserOff::processTriangle(Maillage& m, int a, int b, int c)
{
    Triangle t = Triangle(a, b, c);
    m.addTriangle(t);

    if(m.getSommet(a)->triangle == -1)
    {
        m.getSommet(a)->triangle = m.sizeTriangles()-1;
    }
    if(m.getSommet(b)->triangle == -1)
    {
        m.getSommet(b)->triangle = m.sizeTriangles()-1;
    }
    if(m.getSommet(c)->triangle == -1)
    {
        m.getSommet(c)->triangle = m.sizeTriangles()-1;
    }

    linkTriangles(m, a, b);
    linkTriangles(m, b, c);
    linkTriangles(m, c, a);
}

void ParserOff::linkTriangles(Maillage& m, int a, int b)
{
    Triangle* t = m.getTriangle(m.sizeTriangles() - 1);
    if(areteTriangle.find(QPair<int,int>(b, a)) != areteTriangle.end())
    {
        int indexT2 = areteTriangle[QPair<int,int>(b, a)];
        Triangle* t2 = m.getTriangle(indexT2);
        t->triangles[t->indexOtherSommet(a, b)] = indexT2;
        t2->triangles[t2->indexOtherSommet(a, b)] = t->index;
        areteTriangle.erase(QPair<int,int>(b, a));
    }
    else
    {
        areteTriangle[QPair<int,int>(a, b)] = m.sizeTriangles()-1;
    }
}
