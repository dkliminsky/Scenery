#ifndef COLOR_H
#define COLOR_H

#include <QGLFunctions>

class Color
{
public:
    Color(GLfloat r=0, GLfloat b=0, GLfloat g=0, GLfloat a=1.0f);
    Color(const Color &color);

    Color & operator=(const Color &color);

    void setRGBA(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

    void randomRGB();

    GLfloat r;
    GLfloat g;
    GLfloat b;
    GLfloat a;
};

#endif // COLOR_H
