#include <QDebug>
#include "cameranode.h"

CameraNode::CameraNode(int device) :
    device(device)
{
    qDebug() << "Constructor Begin: CameraNode";

    openCamera(device);

    qDebug() << "Constructor End: CameraNode";
}

CameraNode::~CameraNode()
{
    qDebug() << "Destructor Begin: CameraNode";
    qDebug() << "Destructor End: CameraNode";
}

void CameraNode::run()
{
    if (capture.isOpened())
        capture >> frame;
}

void CameraNode::openCamera(int device)
{
    capture.open(device);
}
