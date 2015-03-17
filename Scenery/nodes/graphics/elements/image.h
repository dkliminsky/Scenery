#ifndef IMAGE_H
#define IMAGE_H

#include <QOpenGLFunctions>
#include <QImage>
#include <QString>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


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
    GLuint id() { return _id; }

    void set(IplImage *ipl);
    void set(cv::Mat &mat);
    void create(int width, int height, int channels);
    void load(const QString &fileName);

    void bind();
    bool isBind() { return _isBind; }

private:
    void initDefault();


    cv::Mat _mat;
    QString _fileName;

    GLuint _id;
    bool _isBind;
    int bindWidth;
    int bindHeight;
    int bindChannels;
};

#endif // IMAGE_H
