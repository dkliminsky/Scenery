#include "camerapositionnode.h"

CameraPositionNode::CameraPositionNode()
{
    output(PortType::Rect);

    control(x=0, "x", -500, 500);
    control(y=0, "y", -500, 500);
    control(h=200, "width", 0, 1000);
    control(w=200, "height", 0, 1000);
}

void CameraPositionNode::run()
{
    Rect &rect = outputs.at(0)->rect;
    rect.x = x;
    rect.y = y;
    rect.width = w;
    rect.height = h;
}

