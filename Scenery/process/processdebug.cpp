#include "processdebug.h"

ProcessDebug::ProcessDebug(QString name, int width, int height)
{
    this->name = name;
    this->width = width;
    this->height = height;

    debug = cvCreateImage( cvSize(width, height), IPL_DEPTH_8U, 3 );

    cvNamedWindow(name.toStdString().c_str(), CV_WINDOW_FREERATIO);
    //cvNamedWindow("Hit", CV_WINDOW_FREERATIO);
}

ProcessDebug::~ProcessDebug()
{
    cvDestroyAllWindows();
}

void ProcessDebug::show(IplImage *image, Process *process)
{
    if (!image)
        return;

    if (!process->getDebug())
        return;

    cvCopy(image, debug);

    switch (process->getMode()) {
    case Process::ProcessNone:
        break;
    case Process::ProcessColor:
        cvSet(debug, CV_RGB(255,255,255), process->getHit());
        drawAreasReal(debug, process->getAreas(), CV_RGB(255,255,0));
        drawAreas(debug, process->getAreas(), CV_RGB(150,0,0));
        drawSeqAreas(debug, process->getSeqAreas(), CV_RGB(255,0,0));
        break;
    case Process::ProcessMotion:
        cvSet(debug, CV_RGB(255,255,255), process->getHit());
        drawAreasReal(debug, process->getAreas(), CV_RGB(255,255,0));
        drawAreas(debug, process->getAreas(), CV_RGB(150,0,0));
        drawSeqAreas(debug, process->getSeqAreas(), CV_RGB(255,0,0));
        break;
    case Process::ProcessHaar:
        drawAreasReal(debug, process->getAreas(), CV_RGB(255,255,0));
        drawAreas(debug, process->getAreas(), CV_RGB(255,0,0));
        drawSeqAreas(debug, process->getSeqAreas(), CV_RGB(255,0,0));
        break;
    case Process::ProcessContour:
        cvSet(debug, CV_RGB(255,255,255), process->getHit());
        drawAreasReal(debug, process->getAreas(), CV_RGB(255,255,0));
        drawAreas(debug, process->getAreas(), CV_RGB(150,0,0));
        drawSeqAreas(debug, process->getSeqAreas(), CV_RGB(255,0,0));
        //        for(CvSeq* seq = process->getContours(); seq != 0; seq = seq->h_next){
        //            // нарисовать контур
        //            cvDrawContours(image, seq, CV_RGB(0,0,250), CV_RGB(0,0,250), 0, 1, 8);
        //            // Работаем с точками последовательности
        //             //CvPoint* p = (CvPoint*)cvGetSeqElem ( seq, i );
        //        }
        break;
    case Process::ProcessHoughCircles:
        drawAreasReal(debug, process->getAreas(), CV_RGB(255,255,0));
        drawAreas(debug, process->getAreas(), CV_RGB(255,0,0), 1);
        drawSeqAreas(debug, process->getSeqAreas(), CV_RGB(255,0,0), 1);
        break;


    }

    drawTransform(debug, process, CV_RGB(255,255,0) );

    cvShowImage(name.toStdString().c_str(), debug);
    //cvShowImage("Hit", process->getHitImage());
}

void ProcessDebug::drawAreas(IplImage *image, Areas &areas, CvScalar color, int type)
{
    vector<Area>::iterator it = areas.begin();
    for (; it != areas.end(); ++it) {
        Area &area = *it;
        if ( type ==0 ) {
            cvRectangle(image,
                        cvPoint(area.pt[0]-area.width/2, area.pt[1]-area.height/2),
                        cvPoint(area.pt[0]+area.width/2, area.pt[1]+area.height/2),
                        color, 1 );
        }
        else {
            cvCircle(image, cvPoint(area.pt[0], area.pt[1]),
                     (area.width+area.height)/2, color, 1);
        }

    }
}

void ProcessDebug::drawAreasReal(IplImage *image, Areas &areas, CvScalar color, int type)
{
    vector<Area>::iterator it = areas.begin();
    for (; it != areas.end(); ++it) {
        Area &area = *it;
        if ( type ==0 ) {
            cvRectangle(image,
                        cvPoint(area.ptReal[0]-area.widthReal/2,
                                area.ptReal[1]-area.heightReal/2),
                        cvPoint(area.ptReal[0]+area.widthReal/2,
                                area.ptReal[1]+area.heightReal/2),
                        color, 1 );
        }
        else {
            cvCircle(image, cvPoint(area.ptReal[0], area.pt[1]),
                     (area.widthReal+area.heightReal)/2, color, 1);
        }

    }
}

void ProcessDebug::drawSeqAreas(IplImage *image, SeqAreas &seqAreas, CvScalar color, int type)
{
    vector<SeqArea>::iterator it = seqAreas.begin();
    for (; it != seqAreas.end(); ++it) {
        SeqArea &seqArea = *it;
        if ( seqArea.number > 0 ) {

            if (type == 0) {
                cvRectangle(image,
                            cvPoint(seqArea.pt[0]-seqArea.width/2, seqArea.pt[1]-seqArea.height/2),
                            cvPoint(seqArea.pt[0]+seqArea.width/2, seqArea.pt[1]+seqArea.height/2),
                            color, 2 );
            }
            else {
                cvCircle(image, cvPoint(seqArea.pt[0], seqArea.pt[1]),
                         (seqArea.width+seqArea.height)/2, color, 2);

            }

        }
    }

    seqAreasList.append(seqAreas);
    if (seqAreasList.size() > 100)
        seqAreasList.removeFirst();

    for(int i=0; i<seqAreasList.size(); ++i) {
        SeqAreas seqAreas = seqAreasList.at(i);

        vector<SeqArea>::iterator it = seqAreas.begin();
        for (; it != seqAreas.end(); ++it) {
            SeqArea &seqArea = *it;
            //qDebug() << seqArea.number << seqArea.pt[0];

            if ( seqArea.number > 1 ) {
                cvLine(image,
                       cvPoint(seqArea.pt[0], seqArea.pt[1]),
                       cvPoint(seqArea.ptPrev[0], seqArea.ptPrev[1]),
                       color);
            }
        }
    }
}

void ProcessDebug::drawTransform(IplImage *image, Process *process, CvScalar color)
{
    int p[4][2];

    process->transform2D(0,                        0, p[0][0], p[0][1]);
    process->transform2D(image->width,             0, p[1][0], p[1][1]);
    process->transform2D(image->width, image->height, p[2][0], p[2][1]);
    process->transform2D(0,            image->height, p[3][0], p[3][1]);

    cvLine(image, cvPoint(p[0][0], p[0][1]), cvPoint(p[1][0], p[1][1]), color, 2);
    cvLine(image, cvPoint(p[1][0], p[1][1]), cvPoint(p[2][0], p[2][1]), color, 2);
    cvLine(image, cvPoint(p[2][0], p[2][1]), cvPoint(p[3][0], p[3][1]), color, 2);
    cvLine(image, cvPoint(p[3][0], p[3][1]), cvPoint(p[0][0], p[0][1]), color, 2);
}
