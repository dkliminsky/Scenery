#include "cameranode.h"


CameraNode::CameraNode(int device) :
    device(device)
{
    METHOD_BEGIN

    outputs.append(new Port(PortType::Mat));
    openCamera(device);

    METHOD_END
}

void CameraNode::run()
{
    if (capture.isOpened())
        capture >> outputs.at(0)->mat;
}

void CameraNode::openCamera(int device)
{
    capture.open(device);
}
