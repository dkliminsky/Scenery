#include "debugnode.h"
#include <QDebug>


DebugNode::DebugNode()
{
    qDebug() << "CameraNode: Constructor Begin";

    in.append(new Link(LinkType::Mat));

    qDebug() << "CameraNode: Constructor End";
}

void DebugNode::run()
{
    Mat &frame = in.at(0)->mat;
    if (frame.rows > 0 && frame.cols > 0)
        imshow("Debug", frame);
}
