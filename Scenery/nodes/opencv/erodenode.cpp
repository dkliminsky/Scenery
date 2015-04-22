#include "erodenode.h"

ErodeNode::ErodeNode()
{
    input(PortType::Mat);
    output(PortType::Mat);
    addControl(erosion_size=2, "Erosion size", 0, 100);
}

void ErodeNode::run()
{
    Mat &in_mat  =  inputs.at(0)->mat;
    Mat &out_mat = outputs.at(0)->mat;

    if (in_mat.empty())
        return;

    Mat element = cv::getStructuringElement(cv::MORPH_RECT,
                                            Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                                            Point( erosion_size, erosion_size ));
    cv::erode(in_mat, out_mat, element);
}
