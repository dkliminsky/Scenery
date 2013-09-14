#include "saveimagethread.h"
#include <QFile>
#include <QDataStream>

SaveImageThread::SaveImageThread(cv::Mat &mat, QString fileName) :
    mat(mat)
{
    this->fileName = fileName;
}

void SaveImageThread::run()
{
    saveImage(mat, fileName);
}

void SaveImageThread::saveImage(cv::Mat &mat, const QString &fileName)
{
    //QTime time;
    //time.start();
    QFile file(fileName);

    if (file.open(QIODevice::WriteOnly)) {
        QDataStream stream(&file);
        //stream.setVersion(QDataStream::Qt_5_1);
        stream.writeRawData(reinterpret_cast<char *>(mat.data), mat.rows*mat.cols*mat.channels());
        if(stream.status() != QDataStream::Ok)
        {
            qDebug() << "Error writign file: " << fileName;
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

    //qDebug() << "Save time: " << time.elapsed();
}
