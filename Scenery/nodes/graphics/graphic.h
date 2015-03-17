#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <QPainter>
#include <QVector>
#include <QOpenGLFunctions>

#include "elements/elements.h"


enum class ReverseType { None, Vertical, Horizontal };


class Graphic
{
public:
    Graphic();
    ~Graphic();

    QPainter *painter() { return _painter; }

    int width() { return _widthScene; }
    int height() { return _heightScene; }
    void size(int width, int height);

    void color(GLfloat r, GLfloat g, GLfloat b, GLfloat a=1);
    void color(const Color &color);

    void background(GLfloat r, GLfloat g, GLfloat b, GLfloat a=1);
    void background(const Color &color);

    void draw(Image *image, GLfloat x, GLfloat y, GLfloat width, GLfloat height,
               GLfloat angle=0, ReverseType reverse=ReverseType::None);

    void flush();

protected:

private:
    friend class View;
    friend class ScenesNode;

    QPainter *_painter;

    int _widthView;     // реальный размер окна в пикселах
    int _heightView;    //

    int _widthScene;     // желаемый размер окна в виртуальных пикселах
    int _heightScene;    //

    struct ImageBuffer {
        GLuint id;

        float x1;
        float y1;
        float x2;
        float y2;
        float x3;
        float y3;
        float x4;
        float y4;

        float r;
        float g;
        float b;
        float a;
    };

    QVector<ImageBuffer> imageBuffers;
    Color curColor;
};

#endif // GRAPHIC_H
