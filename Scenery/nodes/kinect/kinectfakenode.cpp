#include "kinectfakenode.h"
#include <QtGlobal>


KinectNode::KinectNode(int device)
{
    METHOD_BEGIN

    Q_UNUSED(device)

    out.append(new Port(PortType::Mat));
    out.append(new Port(PortType::Mat));

    out.at(0)->mat.create(Size(640, 480), COLOR_TYPE);
    out.at(1)->mat.create(Size(320, 240), DEPTH_TYPE);

    METHOD_END
}
