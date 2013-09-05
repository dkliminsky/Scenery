#include "storeimage.h"

StoreImage::StoreImage()
{
    task = NONE;
}

void StoreImage::threadSaveImage(cv::Mat &mat, QString fileName)
{
    this->wait();
    task = SAVE_IMAGE;
    this->mat = mat;
    this->fileName = fileName;
    this->start();
}

void StoreImage::threadLoadImage(cv::Mat *mat, QString fileName)
{
    this->wait();
    task = LOAD_IMAGE;
    this->mat = mat;
    this->fileName = fileName;
    this->start();
}

void StoreImage::run()
{
    switch (task) {
    case NONE:
        break;
    case SAVE_IMAGE:
        saveImage(mat, fileName);
        break;
    case LOAD_IMAGE:
        loadImage(mat, fileName);
        break;
    }
}

void StoreImage::saveImage(cv::Mat *mat, const QString &fileName)
{
    std::vector<int> compression_params;
    compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(3);
    cv::imwrite(fileName.toStdString(), mat, compression_params);

}

void StoreImage::loadImage(cv::Mat *mat, const QString &fileName)
{
    mat = cv::imread(fileName.toStdString(), CV_LOAD_IMAGE_UNCHANGED);
    //IplImage ipl = mat;
    create(mat.cols, mat.rows, mat.channels());
    _iplImage->imageData =  reinterpret_cast<char *>(mat.data);
    //cvCopy(&ipl, _iplImage);
}
