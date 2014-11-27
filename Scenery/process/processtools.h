#ifndef PROCESSTOOLS_H
#define PROCESSTOOLS_H


#define M_PI	3.14159265358979323846	/* pi */

class ProcessTools
{
public:
    ProcessTools();

    double length(int pt1[2], int pt2[2]);
    double angle(int pt0[2], int pt[2]);

    unsigned char rgb2gray(unsigned char &r, unsigned char &g, unsigned char &b);

    static unsigned char *HTable;
    static unsigned char *STable;
    static unsigned char *VTable;

    static void initRGB2HSV();

    static void RGB2HSV(unsigned char *h, unsigned char *s, unsigned char *v,
                 unsigned char r, unsigned char g, unsigned char b);

private:
    static void RGB2HSVi(int &h, int &s, int &v,
                  int  r, int  g, int  b);

    static void RGB2HSVd(double &h, double &s, double &v,
                  double  r, double  g, double  b);

};

#endif // PROCESSTOOLS_H
