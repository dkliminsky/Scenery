#include "debug.h"
#include "cameranode.h"


CameraNode::CameraNode(int device) :
    device(device)
{
    METHOD_BEGIN

    out.append(new Port(PortType::Mat));
    openCamera(device);

    METHOD_END
}

void CameraNode::run()
{
    //METHOD_BEGIN

    if (capture.isOpened())
        capture >> out.at(0)->mat;

    //METHOD_END
}

void CameraNode::openCamera(int device)
{
    capture.open(device);
}
