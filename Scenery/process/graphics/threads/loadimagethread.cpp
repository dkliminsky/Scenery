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

    if ( fileName.right(4) == ".bin") {
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
    }
    else {
        mat = cv::imread(fileName.toStdString(), CV_LOAD_IMAGE_UNCHANGED);
    }

    //qDebug() << "Load time: " << time.elapsed();
}
