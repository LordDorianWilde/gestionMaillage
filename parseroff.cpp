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
            processTriangle(coord[1].toInt(), coord[2].toInt(), coord[3].toInt());
        }
    }

    return m;
}

void ParserOff::processSommet(float a, float b, float c)
{
    Sommet s = Sommet(&m, a, b, c);
    m.addSommet(s);
}

void ParserOff::processTriangle(int a, int b, int c)
{
    Triangle t = Triangle(&m, a, b, c);
    m.addTriangle(t);

    if(m.getSommet(a)->getTriangle() == -1)
    {
        m.getSommet(a)->setTriangle(m.sizeTriangles()-1);
    }
    if(m.getSommet(b)->getTriangle() == -1)
    {
        m.getSommet(b)->setTriangle(m.sizeTriangles()-1);
    }
    if(m.getSommet(c)->getTriangle() == -1)
    {
        m.getSommet(c)->setTriangle(m.sizeTriangles()-1);
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
        t->setTriangle(t->indexOtherSommet(a, b), indexT2);
        t2->setTriangle(t2->indexOtherSommet(a, b), t->getIndex());
        areteTriangle.erase(QPair<int,int>(b, a));
    }
    else
    {
        areteTriangle[QPair<int,int>(a, b)] = m.sizeTriangles()-1;
    }
}
