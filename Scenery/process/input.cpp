#include "input.h"
#include <QDebug>

Input::Input(Device device, QString name, int width, int height)
{
    qDebug() << "Constructor Begin: Input";

    this->device = device;
    this->name = name;
    this->width = width;
    this->height = height;

    capture = 0;
    switch (device) {
    case None:
        break;
    case Camera:
        initCamera();
        break;
    case Video:
        initVideo();
        break;
    }

    curFrame = 0;
    for ( int i=0; i<STORE_FRAMES; i++) {
        arrFrame[i] = cvCreateImage( cvSize(this->width, this->height), IPL_DEPTH_8U, 3 );
    }

    frame = arrFrame[0];

    timeMean = 0;
    timeNum = 0;
    timeResult = 0;

    qDebug() << "Constructor End: Input";
}

Input::~Input()
{
    qDebug() << "Destructor Begin: Input";

    wait();
    if (capture) {
        cvReleaseCapture(&capture);
    }

    for ( int i=0; i<STORE_FRAMES; i++) {
        cvReleaseImage(&arrFrame[i]);
    }

    qDebug() << "Destructor End: Input";
}

void Input::run()
{
    QTime time;
    time.start();

    if (!capture)
        return;

    IplImage *newFrame = cvQueryFrame(capture);
    if ( !newFrame )
        return;

    curFrame++;
    if (curFrame == STORE_FRAMES)
        curFrame = 0;

    frame = arrFrame[curFrame];
    cvCopy(newFrame, frame);

    timeMean += time.elapsed();
    timeNum++;
    if ( timeNum == 10 ) {
        timeResult = timeMean/10;
        timeMean = 0;
        timeNum = 0;
    }
}

void Input::initCamera()
{
    // получаем любую подключённую камеру
    // capture = cvCreateCameraCapture(CV_CAP_ANY);
    capture = cvCreateCameraCapture(name.toInt());
    assert( capture );

    if ( !(width <= 0 || height <= 0) ) {
        cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, width);
        cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, height);
    }

    //cvSetCaptureProperty(capture, CV_CAP_PROP_FPS, 30);
    //cvSetCaptureProperty(capture, CV_CAP_PROP_CONTRAST, 50);

    int realWidth =  (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);
    int realHeight = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);
    qDebug() << "Resolution camera:" << realWidth << realHeight;

    width = realWidth;
    height = realHeight;
}

void Input::initVideo()
{
    capture = cvCreateFileCapture(name.toStdString().c_str());
    assert( capture );

    int realWidth =  (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);
    int realHeight = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);
    qDebug() << "Resolution video:" << realWidth << realHeight;

    width = realWidth;
    height = realHeight;
}
