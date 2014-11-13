#ifndef CAMERANODE_H
#define CAMERANODE_H

#include <opencv2/opencv.hpp>
#include "process/node.h"

using namespace cv;


class CameraNode : public Node
{
public:
    CameraNode(int device=0);
    virtual const QString name() { return "Camera"; }
    virtual const QString tooltip() { return "Camera capture"; }

protected:
    void run();

private:
    int device;
    VideoCapture capture;

    void openCamera(int device);
};

#endif // CAMERANODE_H
