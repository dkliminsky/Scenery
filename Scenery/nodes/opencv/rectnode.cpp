#include "rectnode.h"

RectNode::RectNode()
{
    output(PortType::Rect);

    addControl(x=160, "x", -500, 500);
    addControl(y=120, "y", -500, 500);
    addControl(h=320, "width", 0, 1000);
    addControl(w=240, "height", 0, 1000);
}

void RectNode::run()
{
    Rect &rect = outputs.at(0)->rect;
    rect.x = x;
    rect.y = y;
    rect.width = w;
    rect.height = h;
}

