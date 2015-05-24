#include "dilatenode.h"

DilateNode::DilateNode()
{
    addInput("mat", PortType::Mat);
    addOutput("mat", PortType::Mat);
    addControl(dilation_size=2, "Erosion size", 0, 100);
}

void DilateNode::run()
{
    Mat &mat_in = input("mat")->mat;
    Mat &mat_out = output("mat")->mat;

    if (mat_in.empty())
        return;

    Mat element = cv::getStructuringElement(cv::MORPH_RECT,
                                            Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                                            Point( dilation_size, dilation_size ));
    cv::dilate(mat_in, mat_out, element);
}
