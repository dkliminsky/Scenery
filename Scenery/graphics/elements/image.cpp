#include "image.h"
#include <QDebug>

Image::Image()
{
    _iplImage = 0;
    isShare = false;
    create(0, 0, 4);
    _fileName = "";
    init();
}

Image::Image(Image *image)
{
    _iplImage = cvCloneImage(image->iplImage());
    isShare = false;
    _fileName = "";
    init();
}

Image::Image(int width, int height, int channels)
{
    _iplImage = 0;
    isShare = false;
    create(width, height, channels);
    _fileName = "";
    init();
}

Image::Image(const QString &fileName)
{
    _iplImage = 0;
    isShare = false;
    load(fileName);
    init();
}

Image::~Image()
{
    if (!isShare) {
        cvReleaseImage(&_iplImage);
    }
}

void Image::bind()
{
    if (width() && height()) {

        int internalformat;
        int format;
        if (channels() == 4) {
            internalformat = GL_RGBA;
            format = GL_BGRA;
        }
        else if (channels() == 3) {
            internalformat = GL_RGB;
            format = GL_BGR;
        }
        else {
            qDebug() << "Image: Error channels";
            return;
        }

        if (!bindId || width() != bindWidth || height() != bindHeight ||
            channels() != bindChannels) {

            if (bindId) {
                glDeleteTextures(1, &bindId);
            }

            glEnable(GL_TEXTURE_2D);
            GLuint gl_id;
            glGenTextures(1, &gl_id);
            glBindTexture(GL_TEXTURE_2D, gl_id);
            glTexImage2D(GL_TEXTURE_2D, 0, internalformat, width(), height(),
                         0, format, GL_UNSIGNED_BYTE, data());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            // задаём линейную фильтрацию вдали:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glDisable(GL_TEXTURE_2D);

            bindId = gl_id;
            bindWidth = width();
            bindHeight = height();
            bindChannels = channels();

            qDebug() << "Bind Image" << gl_id;
        }
        else {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, bindId);
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0.0f, 0.0f, width(), height(),
                            format, GL_UNSIGNED_BYTE, data());
            glDisable(GL_TEXTURE_2D);
        }
    }
}

void Image::set(IplImage *iplImage)
{
    if (!isShare) {
        cvReleaseImage(&this->_iplImage);
        isShare = true;
    }
    this->_iplImage = iplImage;
}

void Image::create(int width, int height, int channels)
{
    if (_iplImage)
        cvReleaseImage(&_iplImage);
    _iplImage = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, channels);
}

void Image::load(const QString &fileName)
{
    QImage img(fileName);
    _fileName = fileName;
    int w = img.width();
    int h = img.height();
    int c = 4; // !!
    create(w, h, c);

    for (int j=0; j<h; j++) {
        for (int i=0; i<w; i++) {
            _iplImage->imageData[j*w*4+i*4+0] = (char)qBlue(img.pixel(i, j));
            _iplImage->imageData[j*w*4+i*4+1] = (char)qGreen(img.pixel(i, j));
            _iplImage->imageData[j*w*4+i*4+2] = (char)qRed(img.pixel(i, j));
            _iplImage->imageData[j*w*4+i*4+3] = (char)qAlpha(img.pixel(i, j));
        }
    }
}

void Image::init()
{
    bindId = 0;
    bindWidth = 0;
    bindHeight = 0;
    bindChannels = 0;
}

