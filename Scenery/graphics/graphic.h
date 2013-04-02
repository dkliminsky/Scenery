#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <QGLFunctions>
#include <QVector>

#include "view.h"
#include "utils.h"
#include "elements/image.h"
#include "elements/color.h"
#include "elements/point.h"


class Graphic: public Utils
{
public:
    Graphic();

    Image *loadImage(const QString &fileName);
    void image(Image *img, GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLfloat angle=0);
    void line(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
    void line(Image *img, GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
    void bezier(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2,
                GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4);
    void bezier(Image *img, GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2,
                            GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4);

    void color(GLfloat r, GLfloat g, GLfloat b, GLfloat a=1);
    void color(const Color &color);
    void background(GLfloat r, GLfloat g, GLfloat b, GLfloat a=1);
    void background(const Color &color);
    void lineWidth(GLfloat width);

    void size(int widthView, int heightView);
    void flush();

protected:
    View *view;

    int widthView;
    int heightView;
    int widthScene;
    int heightScene;

    void sceneChanged();

private:

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

    struct LineBuffer {
        GLuint id;

        float x1;
        float y1;
        float x2;
        float y2;

        float r;
        float g;
        float b;
        float a;
    };

    QVector<ImageBuffer> imageBuffers;
    Color curColor;
    GLfloat lineWidth_;

};

#endif // GRAPHIC_H
