#include "sommet.h"

Sommet::Sommet(float a, float b, float c)
{
    coordonnees[0] = a;
    coordonnees[1] = b;
    coordonnees[2] = c;
    index = -1;
    triangle = -1;
}
Sommet::Sommet()
{
    coordonnees[0] = 0;
    coordonnees[1] = 0;
    coordonnees[2] = 0;
    index = -1;
    triangle = -1;
}

Sommet::Sommet(float a, float b, float c, int t)
{
    coordonnees[0] = a;
    coordonnees[1] = b;
    coordonnees[2] = c;
    index = -1;
    triangle = t;
}
