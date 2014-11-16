#include "erodenode.h"

ErodeNode::ErodeNode()
{
    METHOD_BEGIN

     in.append(new Port(PortType::Mat));
    out.append(new Port(PortType::Mat));

    controls.append(new ControlInt(&erosion_size, "Erosion size", 0, 30));

    METHOD_END
}

void ErodeNode::run()
{
    Mat &in_mat  =  in.at(0)->mat;
    Mat &out_mat = out.at(0)->mat;

    if (in_mat.empty())
        return;

    int erosion_size = 2;

    Mat element = cv::getStructuringElement(cv::MORPH_RECT,
                                            Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                                            Point( erosion_size, erosion_size ));
    cv::erode(in_mat, out_mat, element);
}
