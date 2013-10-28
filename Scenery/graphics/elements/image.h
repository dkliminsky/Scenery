#ifndef IMAGE_H
#define IMAGE_H

#include <QGLFunctions>
#include <QImage>
#include <QString>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "rect.h"

class Image
{
public:
    Image();
    Image(Image *image);
    Image(int width, int height, int channels);
    Image(const QString &fileName);

    int width() { return _mat.cols; }
    int height() { return _mat.rows; }
    int channels() { return _mat.channels(); }
    int step() { return width() * channels(); }
    int size() { return width() * height() * channels(); }
    uchar *data() { return _mat.data; }
    cv::Mat &mat() { return _mat; }

    QString fileName() { return _fileName; }
    GLuint id() { return bindId; }
    RectF texCoords() { return _texCoords; }
    void setTexCoords(float x1, float y1, float x2, float y2);

    void set(IplImage *ipl);
    void bind();
    void create(int width, int height, int channels);

    void load(const QString &fileName);
    void save(const QString &fileName);

private:
    cv::Mat _mat;
    QString _fileName;

    GLuint bindId;
    RectF _texCoords;
    int bindWidth;
    int bindHeight;
    int bindChannels;

    void initDefault();
};

#endif // IMAGE_H
