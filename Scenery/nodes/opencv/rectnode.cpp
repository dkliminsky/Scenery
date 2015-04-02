#include "rectnode.h"

RectNode::RectNode()
{
    output(PortType::Rect);

    control(x=160, "x", -500, 500);
    control(y=120, "y", -500, 500);
    control(h=320, "width", 0, 1000);
    control(w=240, "height", 0, 1000);
}

void RectNode::run()
{
    Rect &rect = outputs.at(0)->rect;
    rect.x = x;
    rect.y = y;
    rect.width = w;
    rect.height = h;
}

