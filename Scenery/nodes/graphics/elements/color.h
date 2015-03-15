#ifndef COLOR_H
#define COLOR_H

#include <QOpenGLFunctions>


class Color
{
public:
    Color(GLfloat r=0, GLfloat b=0, GLfloat g=0, GLfloat a=1.0f);
    Color(const Color &color);

    Color & operator=(const Color &color);
    void setRGBA(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void setRGB(GLfloat r, GLfloat g, GLfloat b);

    void randomRGB();

    GLfloat r;
    GLfloat g;
    GLfloat b;
    GLfloat a;
};

#endif // COLOR_H
