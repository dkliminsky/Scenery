#include "tasks.h"



void Tasks::run()
{

}

void Tasks::saveImage(IplImage *image, const QString &fileName)
{
    cv::Mat mat(image);
    std::vector<int> compression_params;
    compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(3);
    cv::imwrite(fileName.toStdString(), mat, compression_params);
}

void Tasks::loadImage(IplImage *image, const QString &fileName)
{

}
