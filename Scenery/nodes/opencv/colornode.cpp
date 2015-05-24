#include "colornode.h"


ColorNode::ColorNode()
{
    METHOD_BEGIN

    addInput("mat", PortType::Mat);
    addOutput("mat", PortType::Mat);

    METHOD_END
}

void ColorNode::run()
{
    Mat &mat_in = input("mat")->mat;
    Mat &mat_out = output("mat")->mat;

    cvtColor(mat_in, mat_out, COLOR_RGB2GRAY);
}
