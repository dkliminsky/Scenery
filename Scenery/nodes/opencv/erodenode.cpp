#include "erodenode.h"

ErodeNode::ErodeNode()
{
    addInput("mat", PortType::Mat);
    addOutput("mat", PortType::Mat);
    addControl(erosion_size=2, "Erosion size", 0, 100);
}

void ErodeNode::run()
{
    Mat &in_mat  = input("mat")->mat;
    Mat &out_mat = output("mat")->mat;

    if (in_mat.empty())
        return;

    Mat element = cv::getStructuringElement(cv::MORPH_RECT,
                                            Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                                            Point( erosion_size, erosion_size ));
    cv::erode(in_mat, out_mat, element);
}
