#ifndef STOREIMAGE_H
#define STOREIMAGE_H

#include <QString>
#include <QThread>
#include <opencv2/highgui/highgui.hpp>

class StoreImage : public QThread
{
    Q_OBJECT
public:
    explicit StoreImage();

    void threadSaveImage(cv::Mat &mat, QString fileName);
    void threadLoadImage(cv::Mat &mat, QString fileName);

    void run();

    static void saveImage(cv::Mat &mat, const QString &fileName);
    static void loadImage(cv::Mat &mat, const QString &fileName);

private:
    cv::Mat *mat;
    QString fileName;

    enum Task {
        NONE,
        SAVE_IMAGE,
        LOAD_IMAGE
    } task;
    
signals:
    
public slots:
    
};

#endif // STOREIMAGE_H
