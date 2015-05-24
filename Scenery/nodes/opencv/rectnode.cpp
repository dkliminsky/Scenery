#include "rectnode.h"

RectNode::RectNode()
{
    addOutput("rect", PortType::Rect);

    addControl(x=160, "x", -500, 500);
    addControl(y=120, "y", -500, 500);
    addControl(w=320, "width", 0, 1000);
    addControl(h=240, "height", 0, 1000);
}

void RectNode::run()
{
    Rect &rect = output("rect")->rect;
    rect.x = x;
    rect.y = y;
    rect.width = w;
    rect.height = h;
}

