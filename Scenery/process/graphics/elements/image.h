#ifndef IMAGE_H
#define IMAGE_H

#include <QGLFunctions>
#include <QImage>
#include <QString>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "../threads/saveimagethread.h"
#include "../threads/loadimagethread.h"

class Image
{
public:
    Image();
    Image(Image *image);
    Image(int width, int height, int channels);
    Image(const QString &fileName);
    ~Image();

    int width() { return _mat.cols; }
    int height() { return _mat.rows; }
    int channels() { return _mat.channels(); }
    int step() { return width() * channels(); }
    int size() { return width() * height() * channels(); }
    uchar *data() { return _mat.data; }
    cv::Mat &mat() { return _mat; }

    QString fileName() { return _fileName; }
    GLuint id() { return bindId; }

    void set(IplImage *ipl);
    void set(cv::Mat &mat);
    void bind();
    void create(int width, int height, int channels);

    void load(const QString &fileName);
    void save(const QString &fileName);

    void saveThread(const QString &fileName);
    void saveWait();

private:
    cv::Mat _mat;
    QString _fileName;

    SaveImageThread *saveImageThread;

    GLuint bindId;
    int bindWidth;
    int bindHeight;
    int bindChannels;

    void initDefault();
};

#endif // IMAGE_H
