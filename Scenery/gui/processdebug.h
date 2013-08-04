#ifndef DEBUGWINDOW_H
#define DEBUGWINDOW_H

#include <QList>
#include <opencv/cv.h>
#include <opencv/highgui.h>

#include "process/process.h"

class ProcessDebug
{
public:
    ProcessDebug(QString name, int width, int height);
    ~ProcessDebug();

    void show(IplImage *image, Process *process);

private:
    QString name;
    int width;
    int height;

    QList<SeqAreas> seqAreasList;
    IplImage *debug;

    void drawAreas(IplImage *image, Areas &areas, CvScalar color, int type = 0);
    void drawAreasReal(IplImage *image, Areas &areas, CvScalar color, int type = 0);
    void drawSeqAreas(IplImage *image, SeqAreas &seqAreas, CvScalar color, int type = 0);
    void drawTransform(IplImage *image, Process *process, CvScalar color);
};

#endif // DEBUGWINDOW_H
