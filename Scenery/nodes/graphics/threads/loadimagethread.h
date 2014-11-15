#ifndef LOADIMAGETHREAD_H
#define LOADIMAGETHREAD_H

#include <QTime>
#include <QDebug>
#include <QThread>
#include <opencv2/highgui/highgui.hpp>

class LoadImageThread : public QThread
{
	Q_OBJECT
public:
    explicit LoadImageThread(cv::Mat &mat, QString fileName);
    void run();

    static void loadImage(cv::Mat &mat, const QString &fileName);

private:
    cv::Mat &mat;
    QString fileName;
    
signals:
    
public slots:
    
};

#endif // LOADIMAGETHREAD_H
