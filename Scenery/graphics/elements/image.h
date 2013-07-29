#ifndef IMAGE_H
#define IMAGE_H

#include <QGLFunctions>
#include <QImage>
#include <QString>

class Image : public QImage
{
public:
    Image(const QString &name, GLuint id=0);
    QString name() { return _name; }
    GLuint id() { return _id; }

    void _setId(GLuint id) { _id = id; }

private:
    GLuint _id;
    QString _name;

};

#endif // IMAGE_H
