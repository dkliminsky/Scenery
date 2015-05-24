#include "kinectfakenode.h"
#include <QtGlobal>


KinectNode::KinectNode(int device)
{
    METHOD_BEGIN

    Q_UNUSED(device)

    _outputs.append(new Port(PortType::Mat));
    _outputs.append(new Port(PortType::Mat));

    _outputs.at(0)->mat.create(Size(640, 480), COLOR_TYPE);
    _outputs.at(1)->mat.create(Size(320, 240), DEPTH_TYPE);

    qDebug() << "Kinect: init fake kinect";

    METHOD_END
}
