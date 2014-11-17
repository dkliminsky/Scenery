#include "debugnode.h"
#include "debug.h"


DebugNode::DebugNode()
{
    METHOD_BEGIN

    num = qrand();
    inputs.append(new Port(PortType::Mat));

    METHOD_END
}

void DebugNode::run()
{
    Mat &frame = inputs.at(0)->mat;
    if (frame.rows > 0 && frame.cols > 0)
        imshow(QString("Debug %1").arg(num).toStdString(), frame);
}
