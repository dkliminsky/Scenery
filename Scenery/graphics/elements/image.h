#ifndef IMAGE_H
#define IMAGE_H

#include <QGLFunctions>
#include <QImage>
#include <QString>

class Image
{
public:
    Image();
    Image(int width, int height, int channels);
    Image(const QString &fileName);

    int width() { return _width; }
    int height() { return _height; }
    int channels() { return _channels; }
    int size() { return _width * _height * _channels; }
    char *data() { return _data; }

    QString fileName() { return _name; }
    GLuint id() { return bindId; }

    void set(char *data, int width, int height, int channels);
    void update(char *data);
    void bind();
    void load(const QString &fileName);

private:
    char *_data;
    int _width;
    int _height;
    int _channels;

    QString _name;

    GLuint bindId;
    int bindWidth;
    int bindHeight;
    int bindChannels;

    void init();
};

#endif // IMAGE_H
