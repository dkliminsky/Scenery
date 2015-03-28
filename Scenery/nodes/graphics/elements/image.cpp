#include "image.h"
#include <QDebug>

Image::Image()
{
    initDefault();
    create(0, 0, 4);
}

Image::Image(Image *image)
{
    initDefault();
    _mat = image->mat().clone();
}

Image::Image(int width, int height, int channels)
{
    initDefault();
    create(width, height, channels);
}

Image::Image(const QString &fileName)
{
    initDefault();
    load(fileName);
}

void Image::initDefault()
{
    _fileName = "";
    _id = 0;
    _isBind = false;
    bindWidth = 0;
    bindHeight = 0;
    bindChannels = 0;
    _reverse = ReverseType::None;
}

Image::~Image()
{

}

void Image::set(IplImage *ipl)
{
    create(ipl->width, ipl->height, ipl->nChannels);
    _mat.data = reinterpret_cast<uchar *>(ipl->imageData);
    _isBind = false;
}

void Image::set(cv::Mat &mat)
{
    _mat = mat.clone();
    _isBind = false;
}

void Image::create(int width, int height, int channels)
{
    _mat.create(height, width, CV_8UC(channels));
    _isBind = false;
}

void Image::load(const QString &fileName)
{
    _mat = cv::imread(fileName.toStdString(), CV_LOAD_IMAGE_UNCHANGED);
    _isBind = false;
}

void Image::bind()
{
    if (width() && height()) {
        _isBind = true;

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
            internalformat = GL_RED;
            format = GL_RED;
        }

        if (!_id || width() != bindWidth || height() != bindHeight ||
            channels() != bindChannels) {

            if (_id) {
                glDeleteTextures(1, &_id);
            }

            glEnable(GL_TEXTURE_2D);
            GLuint gl_id;
            glGenTextures(1, &gl_id);
            glBindTexture(GL_TEXTURE_2D, gl_id);
            glTexImage2D(GL_TEXTURE_2D, 0, internalformat, width(), height(),
                         0, format, GL_UNSIGNED_BYTE, data());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glDisable(GL_TEXTURE_2D);

            _id = gl_id;
            bindWidth = width();
            bindHeight = height();
            bindChannels = channels();

            qDebug() << "Bind Image:" << gl_id << width() << height() << channels();
        }
        else {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, _id);
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0.0f, 0.0f, width(), height(),
                            format, GL_UNSIGNED_BYTE, data());
            glDisable(GL_TEXTURE_2D);
        }
    }
}
