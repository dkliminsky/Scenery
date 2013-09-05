#ifndef SAVEIMAGE_H
#define SAVEIMAGE_H

#include <QThread>
#include <opencv2/highgui/highgui.hpp>

class SaveImage : public QThread
{
    Q_OBJECT
public:
    explicit SaveImage(cv::Mat &mat, QString fileName);
    void run();

    static void saveImage(cv::Mat &mat, const QString &fileName);

private:
    cv::Mat &mat;
    QString fileName;
    
signals:
    
public slots:
    
};

#endif // SAVEIMAGE_H
