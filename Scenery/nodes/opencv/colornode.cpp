#include "colornode.h"


ColorNode::ColorNode()
{
    METHOD_BEGIN

    in.append(new Port(PortType::Mat));
    out.append(new Port(PortType::Mat));

    METHOD_END
}

void ColorNode::run()
{
    Mat &mat_in = in.at(0)->mat;
    Mat &mat_out = out.at(0)->mat;

    cvtColor(mat_in, mat_out, COLOR_RGB2GRAY);
}
