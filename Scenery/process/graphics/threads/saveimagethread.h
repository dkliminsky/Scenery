#ifndef SAVEIMAGETHREAD_H
#define SAVEIMAGETHREAD_H

#include <QTime>
#include <QDebug>
#include <QThread>
#include <opencv2/highgui/highgui.hpp>

class SaveImageThread : public QThread
{
    Q_OBJECT
public:
    explicit SaveImageThread(cv::Mat &mat, QString fileName);
    void run();

    static void saveImage(cv::Mat &mat, const QString &fileName);

private:
    cv::Mat &mat;
    QString fileName;
    
signals:
    
public slots:
    
};

#endif // SAVEIMAGETHREAD_H
