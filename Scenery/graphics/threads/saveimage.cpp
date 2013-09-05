#include "saveimage.h"

SaveImage::SaveImage(cv::Mat &mat, QString fileName) :
    mat(mat)
{
    this->fileName = fileName;
}

void SaveImage::run()
{
    saveImage(mat, fileName);
}

void SaveImage::saveImage(cv::Mat &mat, const QString &fileName)
{
    std::vector<int> compression_params;
    compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(3);
    cv::imwrite(fileName.toStdString(), mat, compression_params);
}
