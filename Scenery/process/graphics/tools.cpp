#include "tools.h"
#include <math.h>
#include <stdlib.h>

int Tools::random(int high)
{
    return rand()%high;
}

bool Tools::chance(double probability)
{
    return (double)rand()/RAND_MAX < probability;
}

float Tools::distance(float x1, float y1, float x2, float y2)
{
    float A = x1 - x2;
    float B = y1 - y2;
    return sqrt(A*A+B*B);
}

double Tools::distance(double x1, double y1, double x2, double y2)
{
    double A = x1 - x2;
    double B = y1 - y2;
    return sqrt(A*A+B*B);
}

float Tools::angle(float x1, float y1, float x2, float y2)
{
    double d = distance(x1, y1, x2, y2);
    double a = 0;

    if (d > 0) {

        // I
        a = acos( (x2 - x1) / d );

        // III
        if ( (x2 < x1) && (y2 > y1) ) {
            a = M_PI + M_PI - a;
        }
        // II
        else if (x2 < x1) {

        }
        // IV
        else if (y2 > y1) {
            a = M_PI + M_PI - a;
        }
    }

    return a;
}

float Tools::pi()
{
    return M_PI;
}

