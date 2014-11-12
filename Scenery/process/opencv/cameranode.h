#ifndef CAMERANODE_H
#define CAMERANODE_H

#include "opencv2/opencv.hpp"

#include "process/node.h"

using namespace cv;

class CameraNode : public ThreadNode
{
public:
    CameraNode(int device=0);
    ~CameraNode();

    virtual const QString name() { return "Camera"; }
    virtual const QString tooltip() { return "Camera capture"; }

protected:
    void run();

private:
    int device;
    VideoCapture capture;
    Mat frame;

    void openCamera(int device);
};

#endif // CAMERANODE_H
