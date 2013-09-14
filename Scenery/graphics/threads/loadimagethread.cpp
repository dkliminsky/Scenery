#include "loadimagethread.h"
#include <QFile>
#include <QDataStream>

LoadImageThread::LoadImageThread(cv::Mat &mat, QString fileName) :
    mat(mat)
{
    this->fileName = fileName;
}

void LoadImageThread::run()
{
    loadImage(mat, fileName);
}

void LoadImageThread::loadImage(cv::Mat &mat, const QString &fileName)
{
    //QTime time;
    //time.start();
    QFile file(fileName);
    mat.create(360, 640, CV_8UC(4));

    if (file.open(QIODevice::ReadOnly)) {
        QDataStream stream(&file);
        //stream.setVersion(QDataStream::Qt_5_1);
        stream.readRawData((reinterpret_cast<char *>(mat.data)), mat.rows*mat.cols*mat.channels());
        if(stream.status() != QDataStream::Ok)
        {
            qDebug() << "Error read file: " << fileName;
        }
        file.close();
    }
    else {
        qDebug() << "Error open file: " << fileName;
    }

    /*
    std::vector<int> compression_params;
    compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(0);
    cv::imwrite(fileName.toStdString(), mat, compression_params);
    */

    //qDebug() << "Load time: " << time.elapsed();
}
