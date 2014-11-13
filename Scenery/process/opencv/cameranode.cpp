#include <QDebug>
#include "cameranode.h"

CameraNode::CameraNode(int device) :
    device(device)
{
    qDebug() << "CameraNode: Constructor Begin";

    out.append(new Link(LinkType::Mat));
    openCamera(device);

    qDebug() << "CameraNode: Constructor End";
}

CameraNode::~CameraNode()
{
    qDebug() << "CameraNode: Destructor Begin";
    qDebug() << "CameraNode: Destructor End";
}

void CameraNode::run()
{
    if (capture.isOpened())
        capture >> out.at(0)->mat;
}

void CameraNode::openCamera(int device)
{
    capture.open(device);
}
