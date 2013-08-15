#include "image.h"
#include <QDebug>

Image::Image()
{
    _name = "";

    _data = 0;
    _width = 0;
    _height = 0;
    _channels = 0;

    init();
}

Image::Image(int width, int height, int channels)
{
    _name = "";

    _data = new char[width * height * channels];
    _width = width;
    _height = height;
    _channels = channels;

    init();
}

Image::Image(const QString &fileName)
{
    load(fileName);
    init();
}

void Image::set(char *data, int width, int height, int channels)
{
    _data = data;
    _width = width;
    _height = height;
    _channels = channels;
}

void Image::update(char *data)
{
    _data = data;
}

void Image::bind()
{
    if (_width && _height) {

        int internalformat;
        int format;
        if (_channels == 4) {
            internalformat = GL_RGBA;
            format = GL_BGRA;
        }
        else if (_channels == 3) {
            internalformat = GL_RGB;
            format = GL_BGR;
        }
        else {
            qDebug() << "Image: Error channels";
            return;
        }

        if (!bindId || _width != bindWidth || _height != bindHeight ||
                    _channels != bindChannels) {

            if (bindId) {
                glDeleteTextures(1, &bindId);
            }

            glEnable(GL_TEXTURE_2D);
            GLuint gl_id;
            glGenTextures(1, &gl_id);
            glBindTexture(GL_TEXTURE_2D, gl_id);
            glTexImage2D(GL_TEXTURE_2D, 0, internalformat, _width, _height,
                        0, format, GL_UNSIGNED_BYTE, _data);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            // задаём линейную фильтрацию вдали:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glDisable(GL_TEXTURE_2D);

            bindId = gl_id;
            bindWidth = _width;
            bindHeight = _height;
            bindChannels = _channels;

            qDebug() << "Bind Image" << gl_id;
        }
        else {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, bindId);
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0.0f, 0.0f, _width, _height,
                            format, GL_UNSIGNED_BYTE, _data);
            glDisable(GL_TEXTURE_2D);
        }
    }
}

void Image::load(const QString &fileName)
{
    QImage img(fileName);
    _name = fileName;
    _width = img.width();
    _height = img.height();
    _channels = 4; // !!
    _data = new char[img.byteCount()];

    for (int j=0; j<_height; j++) {
        for (int i=0; i<_width; i++) {
            _data[j*_width*4+i*4+0] = (char)qBlue(img.pixel(i, j));
            _data[j*_width*4+i*4+1] = (char)qGreen(img.pixel(i, j));
            _data[j*_width*4+i*4+2] = (char)qRed(img.pixel(i, j));
            _data[j*_width*4+i*4+3] = (char)qAlpha(img.pixel(i, j));
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

