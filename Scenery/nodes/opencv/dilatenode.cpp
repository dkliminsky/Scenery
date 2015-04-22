#include "dilatenode.h"

DilateNode::DilateNode()
{
    input(PortType::Mat);
    output(PortType::Mat);
    addControl(dilation_size=2, "Erosion size", 0, 100);
}

void DilateNode::run()
{
    Mat &in_mat  =  inputs.at(0)->mat;
    Mat &out_mat = outputs.at(0)->mat;

    if (in_mat.empty())
        return;

    Mat element = cv::getStructuringElement(cv::MORPH_RECT,
                                            Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                                            Point( dilation_size, dilation_size ));
    cv::dilate(in_mat, out_mat, element);
}
