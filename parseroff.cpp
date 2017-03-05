#include "parseroff.h"

ParserOff::ParserOff()
{
    m = Maillage();
    areteTriangle = map< QPair<int, int>, int>();
}

Maillage ParserOff::parseFichier(QString fileName)
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
            processSommet(coord[0].toFloat(), coord[1].toFloat(), coord[2].toFloat());
        }
        if(coord.size() == 4)
        {
            processTriangle(coord[1].toInt() + 1, coord[2].toInt() + 1, coord[3].toInt() + 1);
        }
    }

    map< QPair<int, int>, int>::iterator it(areteTriangle.begin());
    while(areteTriangle.size() > 0)
    {
        QPair<int, int> arete = (*it).first;
        if(arete.second != 0 && arete.first != 0)
        {
            processTriangle(0, arete.second, arete.first);
            it = areteTriangle.begin();
        }
        else
        {
            it++;
        }

    }

    return m;
}

void ParserOff::processSommet(float a, float b, float c)
{
    Sommet s = Sommet(a, b, c);
    m.addSommet(s);
}

void ParserOff::processTriangle(int a, int b, int c)
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

    linkTriangles(a, b);
    linkTriangles(b, c);
    linkTriangles(c, a);

}

void ParserOff::linkTriangles(int a, int b)
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
