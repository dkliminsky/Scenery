#include "debugnode.h"
#include "debug.h"


DebugNode::DebugNode()
{
    METHOD_BEGIN

    num = qrand();
    in.append(new Port(PortType::Mat));

    METHOD_END
}

void DebugNode::run()
{
    Mat &frame = in.at(0)->mat;
    if (frame.rows > 0 && frame.cols > 0)
        //qDebug() << frame.rows << frame.cols;
        //qDebug() << QString("Debug %1").arg(num);
        imshow(QString("Debug %1").arg(num).toStdString(), frame);
        //imshow("", frame);
}
