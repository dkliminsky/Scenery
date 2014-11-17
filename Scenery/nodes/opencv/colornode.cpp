#include "colornode.h"


ColorNode::ColorNode()
{
    METHOD_BEGIN

    inputs.append(new Port(PortType::Mat));
    outputs.append(new Port(PortType::Mat));

    METHOD_END
}

void ColorNode::run()
{
    Mat &mat_in = inputs.at(0)->mat;
    Mat &mat_out = outputs.at(0)->mat;

    cvtColor(mat_in, mat_out, COLOR_RGB2GRAY);
}
