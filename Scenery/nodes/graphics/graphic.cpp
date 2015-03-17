#include "graphic.h"

#include <QDebug>


Graphic::Graphic() :
    _painter(nullptr),
    _widthView(0),
    _heightView(0),
    _widthScene(100),
    _heightScene(100),
    curColor(1.0f, 1.0f, 1.0f, 1.0f)
{

}

Graphic::~Graphic()
{

}

void Graphic::size(int width, int height)
{
    Q_ASSERT(_painter);

    _widthScene = width;
    _heightScene = height;

    if (width > 0 && height > 0) {
        _painter->scale((qreal)_widthView/(qreal)width,
                        (qreal)_heightView/(qreal)height);
        glScalef((GLfloat)_widthView/(GLfloat)width,
                 (GLfloat)_heightView/(GLfloat)height, 1.0f);
    }
}

void Graphic::color(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    glColor4f(r, g, b, a);
    curColor.r = r;
    curColor.g = g;
    curColor.b = b;
    curColor.a = a;
}

void Graphic::color(const Color &color)
{
    this->color(color.r, color.g, color.b, color.a);
}

void Graphic::background(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Graphic::background(const Color &color)
{
    background(color.r, color.g, color.b, color.a);
}

void Graphic::draw(Image *image, GLfloat x, GLfloat y, GLfloat width, GLfloat height,
                    GLfloat angle, ReverseType reverse)
{
    Q_ASSERT(image);

    if (!image->isBind()) {
        image->bind();
    }

    if (imageBuffers.size() > 0 && imageBuffers.last().id != image->id()) {
        flush();
    }

    GLfloat x1 = x - width/2.0f;
    GLfloat y1 = y - height/2.0f;
    GLfloat x2 = x + width/2.0f;
    GLfloat y2 = y - height/2.0f;
    GLfloat x3 = x + width/2.0f;
    GLfloat y3 = y + height/2.0f;
    GLfloat x4 = x - width/2.0f;
    GLfloat y4 = y + height/2.0f;

    switch (reverse) {
    case ReverseType::None:
        x1 = x - width/2.0;
        y1 = y - height/2.0;
        x2 = x + width/2.0;
        y2 = y - height/2.0;
        x3 = x + width/2.0;
        y3 = y + height/2.0;
        x4 = x - width/2.0;
        y4 = y + height/2.0;
        break;
    case ReverseType::Vertical:
        x1 = x - width/2.0;
        y1 = y + height/2.0;
        x2 = x + width/2.0;
        y2 = y + height/2.0;
        x3 = x + width/2.0;
        y3 = y - height/2.0;
        x4 = x - width/2.0;
        y4 = y - height/2.0;
        break;
    case ReverseType::Horizontal:
        x1 = x + width/2.0;
        y1 = y - height/2.0;
        x2 = x - width/2.0;
        y2 = y - height/2.0;
        x3 = x - width/2.0;
        y3 = y + height/2.0;
        x4 = x + width/2.0;
        y4 = y + height/2.0;
        break;
    }

    if (angle != 0) {
        // Повернем углы прямоугольника относительно координаты x и y

        GLfloat cs = cos(-angle);
        GLfloat sn = sin(-angle);

        // Вычисление вектора перемещения
        GLfloat dx = -cs*x + sn*y + x;
        GLfloat dy = -sn*x - cs*y + y;

        GLfloat qx1 = cs*x1 - sn*y1 + dx;
        GLfloat qy1 = sn*x1 + cs*y1 + dy;
        GLfloat qx2 = cs*x2 - sn*y2 + dx;
        GLfloat qy2 = sn*x2 + cs*y2 + dy;
        GLfloat qx3 = cs*x3 - sn*y3 + dx;
        GLfloat qy3 = sn*x3 + cs*y3 + dy;
        GLfloat qx4 = cs*x4 - sn*y4 + dx;
        GLfloat qy4 = sn*x4 + cs*y4 + dy;

        x1 = qx1; y1 = qy1;
        x2 = qx2; y2 = qy2;
        x3 = qx3; y3 = qy3;
        x4 = qx4; y4 = qy4;
    }

    ImageBuffer buf;
    buf.id = image->id();
    buf.x1 = x1;
    buf.y1 = y1;
    buf.x2 = x2;
    buf.y2 = y2;
    buf.x3 = x3;
    buf.y3 = y3;
    buf.x4 = x4;
    buf.y4 = y4;

    buf.r = curColor.r;
    buf.g = curColor.g;
    buf.b = curColor.b;
    buf.a = curColor.a;
    imageBuffers.append(buf);
}

void Graphic::flush()
{
    int n = imageBuffers.size();

    if (n==0)
        return;

    GLfloat *vertexes = new GLfloat[4*2*n];
    GLfloat *colors = new GLfloat[4*4*n];
    GLfloat *coords = new GLfloat[4*2*n];

    for (int i=0; i<n; i++) {
        const ImageBuffer &buf = imageBuffers.at(i);

        vertexes[i*8+0] = buf.x1;
        vertexes[i*8+1] = buf.y1;
        vertexes[i*8+2] = buf.x2;
        vertexes[i*8+3] = buf.y2;
        vertexes[i*8+4] = buf.x3;
        vertexes[i*8+5] = buf.y3;
        vertexes[i*8+6] = buf.x4;
        vertexes[i*8+7] = buf.y4;

        colors[i*16+0] = buf.r;
        colors[i*16+1] = buf.g;
        colors[i*16+2] = buf.b;
        colors[i*16+3] = buf.a;
        colors[i*16+4] = buf.r;
        colors[i*16+5] = buf.g;
        colors[i*16+6] = buf.b;
        colors[i*16+7] = buf.a;
        colors[i*16+8] = buf.r;
        colors[i*16+9] = buf.g;
        colors[i*16+10] = buf.b;
        colors[i*16+11] = buf.a;
        colors[i*16+12] = buf.r;
        colors[i*16+13] = buf.g;
        colors[i*16+14] = buf.b;
        colors[i*16+15] = buf.a;

        coords[i*8+0] = 0.0f;
        coords[i*8+1] = 0.0f;
        coords[i*8+2] = 1.0f;
        coords[i*8+3] = 0.0f;
        coords[i*8+4] = 1.0f;
        coords[i*8+5] = 1.0f;
        coords[i*8+6] = 0.0f;
        coords[i*8+7] = 1.0f;
    }

    glBindTexture(GL_TEXTURE_2D, imageBuffers.at(0).id);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    //glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

//    GLfloat envColor[4] = {1, 1, 1, 0};
//    glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, envColor);

//    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
    //GLfloat envColor[4] = {curColor.r, curColor.g, curColor.b, curColor.a};
    //glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, envColor);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(2, GL_FLOAT, 0, vertexes);
    glColorPointer(4, GL_FLOAT, 0, colors);
    glTexCoordPointer(2, GL_FLOAT, 0, coords);

    glDrawArrays(GL_QUADS, 0, 4*n);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisable(GL_TEXTURE_2D);

    imageBuffers.clear();
    delete [] vertexes;
    delete [] colors;
    delete [] coords;
}
