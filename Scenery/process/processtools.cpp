#include "processtools.h"
#include <math.h>

unsigned char *ProcessTools::HTable = 0;
unsigned char *ProcessTools::STable = 0;
unsigned char *ProcessTools::VTable = 0;

ProcessTools::ProcessTools()
{
}

double ProcessTools::length(int pt1[], int pt2[])
{
    double A = pt1[0] - pt2[0];
    double B = pt1[1] - pt2[1];
    return sqrt(A*A+B*B);
}

double ProcessTools::angle(int pt0[], int pt[])
{
    double d = length(pt0, pt);
    double a = 0;

    if (d > 0) {

        // I
        a = acos( (pt[0] - pt0[0]) / d );

        // III
        if ( (pt[0] < pt0[0]) && (pt[1] > pt0[1]) ) {
            a = M_PI + M_PI - a;
            //qDebug() << "III " << elem.alpha*180/3.14;
        }
        // II
        else if (pt[0] < pt0[0]) {
            //qDebug() << "II " << elem.alpha*180/3.14;
        }
        // IV
        else if (pt[1] > pt0[1]) {
            a = M_PI + M_PI - a;
            //qDebug() << "IV " << elem.alpha*180/3.14;
        }
    }

    return a;
}

unsigned char ProcessTools::rgb2gray(unsigned char &r, unsigned char &g, unsigned char &b)
{
    return (unsigned char) ( (double)(r)*0.30 + (double)(g)*0.59 + (double)(b)*0.11 );
}

void ProcessTools::initRGB2HSV()
{
    HTable = new unsigned char[256*256*256+256*256+256];
    STable = new unsigned char[256*256*256+256*256+256];
    VTable = new unsigned char[256*256*256+256*256+256];

    for (int r=0; r<=255; r++)
        for(int g=0; g<=255; g++)
            for(int b=0; b<=255; b++)
            {
                int h,s,v;
                RGB2HSVi(h,s,v,r,g,b);

                HTable[r*256*256 + g*256 + b] = (unsigned char)(255.0*(double)h/360.0);
                STable[r*256*256 + g*256 + b] = (unsigned char)s;
                VTable[r*256*256 + g*256 + b] = (unsigned char)v;
            }
}

void ProcessTools::RGB2HSV(unsigned char *h, unsigned char *s, unsigned char *v,
                           unsigned char r, unsigned char g, unsigned char b)
{
    *h = *((unsigned char *)(HTable + r*256*256 + g*256 + b));
    *s = *((unsigned char *)(STable + r*256*256 + g*256 + b));
    *v = *((unsigned char *)(VTable + r*256*256 + g*256 + b));
}

void ProcessTools::RGB2HSVi(int &h, int &s, int &v, int r, int g, int b)
{
    int min, max, delta;
    double dh;

    min = r < g ? r : g;
    min = min < b ? min : b;

    max = r > g ? r : g;
    max = max  > b ? max : b;

    v = max;                 // v
    delta = max - min;
    if( max > 0 && delta > 0 ) {
        s = ((double)delta / (double)max * 255.0);  // s
    } else {
        // r = g = b = 0                        // s = 0, v is undefined
        s = 0;
        h = 0;                            // its now undefined
        return;
    }
    if( r >= max )                           // > is bogus, just keeps compilor happy
        dh = (double)( g - b ) / (double)delta;        // between yellow & magenta
    else
    if( g >= max )
        dh = 2 + (double)( b - r ) / (double)delta;  // between cyan & yellow
    else
        dh = 4 + (double)( r - g ) / (double)delta;  // between magenta & cyan

    dh *= 60;                              // degrees

    if( dh < 0 )
        dh += 360;

    h = (int)dh;
}

void ProcessTools::RGB2HSVd(double &h, double &s, double &v, double r, double g, double b)
{
    double min, max, delta;

    min = r < g ? r : g;
    min = min < b ? min : b;

    max = r > g ? r : g;
    max = max  > b ? max : b;

    v = max;                 // v
    delta = max - min;
    if( max > 0.0 ) {
        s = (delta / max);                  // s
    } else {
        // r = g = b = 0                        // s = 0, v is undefined
        s = 0.0;
        h = NAN;                            // its now undefined
        return;
    }
    if( r >= max )                           // > is bogus, just keeps compilor happy
        h = ( g - b ) / delta;        // between yellow & magenta
    else
    if( g >= max )
        h = 2.0 + ( b - r ) / delta;  // between cyan & yellow
    else
        h = 4.0 + ( r - g ) / delta;  // between magenta & cyan

    h *= 60.0;                              // degrees

    if( h < 0.0 )
        h += 360.0;
}

