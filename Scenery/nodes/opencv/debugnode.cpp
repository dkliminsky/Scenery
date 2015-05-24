#include "debugnode.h"
#include "debug.h"


DebugNode::DebugNode()
{
    METHOD_BEGIN

    num = qrand();
    addInput("mat", PortType::Mat);

    METHOD_END
}

void DebugNode::run()
{
    Mat &frame = input("mat")->mat;
    if (frame.rows > 0 && frame.cols > 0)
        imshow(QString("Debug %1").arg(num).toStdString(), frame);
}
