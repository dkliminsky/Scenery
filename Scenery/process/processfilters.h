#ifndef PROCESSFILTERS_H
#define PROCESSFILTERS_H

#include "processtools.h"

#include <opencv/cxcore.h>
#include <opencv/cvaux.h>

class ProcessFilters : public ProcessTools
{
public:
    ProcessFilters(int width, int height);
    ~ProcessFilters();

    void filterKuwahara(IplImage* image, IplImage *result, int kernel_size);

    void slitImage(IplImage* image);
    IplImage *getSlitImage() { return slit; }

private:
    int width;   // Ширина и высота изображений,
    int height;  // которые будут обрабатываться

    IplImage *gray;
    IplImage *slit;

};

#endif // PROCESSFILTERS_H
