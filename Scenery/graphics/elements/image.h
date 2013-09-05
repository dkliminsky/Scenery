#ifndef IMAGE_H
#define IMAGE_H

#include <QGLFunctions>
#include <QImage>
#include <QString>
#include "opencv2/core/core_c.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "../threads/saveimage.h"

class Image
{
public:
    Image();
    Image(Image *image);
    Image(int width, int height, int channels);
    Image(const QString &fileName);
    ~Image();

    int width() { return _iplImage->width; }
    int height() { return _iplImage->height; }
    int channels() { return _iplImage->nChannels; }
    int step() { return _iplImage->widthStep; }
    int size() { return width() * height() * channels(); }
    char *data() { return _iplImage->imageData; }
    IplImage *iplImage() { return _iplImage; }

    QString fileName() { return _fileName; }
    GLuint id() { return bindId; }

    void bind();
    void set(IplImage *_iplImage);
    void create(int width, int height, int channels);

    void load(const QString &fileName);
    void save(const QString &fileName);

private:
    cv::Mat mat;
    IplImage *_iplImage;
    QString _fileName;
    bool isShare;

    SaveImage saveImageThread;

    GLuint bindId;
    int bindWidth;
    int bindHeight;
    int bindChannels;

    void init();
};

#endif // IMAGE_H
