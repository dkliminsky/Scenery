#include "kinectfakenode.h"
#include <QtGlobal>


KinectNode::KinectNode(int device)
{
    METHOD_BEGIN

    Q_UNUSED(device)

    outputs.append(new Port(PortType::Mat));
    outputs.append(new Port(PortType::Mat));

    outputs.at(0)->mat.create(Size(640, 480), COLOR_TYPE);
    outputs.at(1)->mat.create(Size(320, 240), DEPTH_TYPE);

    qDebug() << "Kinect: init fake kinect";

    METHOD_END
}
