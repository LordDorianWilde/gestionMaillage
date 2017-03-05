#include "triangle.h"

Triangle::Triangle(int a, int b, int c)
{
    sommets.push_back(a);
    sommets.push_back(b);
    sommets.push_back(c);
    index = -1;

    triangles.push_back(-1);
    triangles.push_back(-1);
    triangles.push_back(-1);
}

Triangle::Triangle()
{
    sommets.push_back(0);
    sommets.push_back(0);
    sommets.push_back(0);
    index = -1;

    triangles.push_back(0);
    triangles.push_back(0);
    triangles.push_back(0);
}

Triangle::Triangle(int a, int b, int c, int d, int e, int f)
{
    sommets.push_back(a);
    sommets.push_back(b);
    sommets.push_back(c);
    index = -1;

    triangles.push_back(d);
    triangles.push_back(e);
    triangles.push_back(f);
}

int Triangle::indexOtherSommet(int a, int b)
{
    for(int i = 0; i<3; i++)
    {
        if(sommets[i] != a && sommets[i] != b)
        {
            return i;
        }
    }

    return -1;
}

