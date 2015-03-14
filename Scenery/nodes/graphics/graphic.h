#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <QPainter>
#include <QOpenGLFunctions>


class Graphic
{
public:
    Graphic();

    QPainter *painter() { return _painter; }

    int width() { return _widthView; }
    int height() { return _heightView; }
    void size(int width, int height);

    void background(GLfloat r, GLfloat g, GLfloat b, GLfloat a=1);

protected:

private:
    friend class View;
    friend class ScenesNode;

    QPainter *_painter;

    int _widthView;     // реальный размер окна в пикселах
    int _heightView;    //

    int _widthScene;     // желаемый размер окна в виртуальных пикселах
    int _heightScene;    //

};

#endif // GRAPHIC_H
