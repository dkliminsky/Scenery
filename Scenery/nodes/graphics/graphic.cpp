#include "graphic.h"

#include <QDebug>


Graphic::Graphic() :
    _painter(nullptr),
    _widthView(0),
    _heightView(0),
    _widthScene(100),
    _heightScene(100)
{

}

void Graphic::size(int width, int height)
{
    Q_ASSERT(_painter);

    _widthScene = width;
    _heightScene = height;

    if (width > 0 && height > 0)
        _painter->scale((qreal)_widthView/(qreal)width,
                        (qreal)_heightView/(qreal)height);
        glScalef((GLfloat)_widthView/(GLfloat)width,
                 (GLfloat)_heightView/(GLfloat)height, 1.0f);
}

void Graphic::background(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);

//    glColor4f(r, g, b, a);
//    glBegin(GL_QUADS);
//        glVertex2f(0, 0);
//        glVertex2f(0, _heightView);
//        glVertex2f(_widthView, _heightView);
//        glVertex2f(_widthView, 0);
//    glEnd();
}
