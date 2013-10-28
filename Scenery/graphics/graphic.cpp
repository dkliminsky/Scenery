#include "graphic.h"

#include "tools.h"
#include "elements/rect.h"
#include <math.h>
#include <QDebug>

Graphic::Graphic()
{
    widthView = 0;
    heightView = 0;

    lineWidth_ = 1;
    lineParts_ = 1;
}

void Graphic::size(int width, int height)
{
    this->widthScene = width;
    this->heightScene = height;

    if (width > 0 && height > 0)
        glScalef((GLfloat)widthView/(GLfloat)width,
                 (GLfloat)heightView/(GLfloat)height, 1.0f);
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
    glColor4f(r, g, b, a);
    glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(0, heightView);
        glVertex2f(widthView, heightView);
        glVertex2f(widthView, 0);
    glEnd();
}

void Graphic::background(const Color &color)
{
    background(color.r, color.g, color.b, color.a);
}

void Graphic::lineWidth(GLfloat width)
{
    Q_ASSERT(width >= 0);
    glLineWidth(width);
    lineWidth_ = width;
}

void Graphic::lineParts(int parts)
{
    Q_ASSERT(parts >= 0);
    lineParts_ = parts;
}

void Graphic::image(Image *img, GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLfloat angle)
{
    Q_ASSERT(img);

    if ((imageBuffers.size() > 0 && imageBuffers.last().id != img->id()) ||
         imageBuffers.size() >= INT_MAX) {
        flush();
    }

    GLfloat x1 = x - width/2.0;
    GLfloat y1 = y - height/2.0;
    GLfloat x2 = x + width/2.0;
    GLfloat y2 = y - height/2.0;
    GLfloat x3 = x + width/2.0;
    GLfloat y3 = y + height/2.0;
    GLfloat x4 = x - width/2.0;
    GLfloat y4 = y + height/2.0;

    RectF texCoords = img->texCoords();
    GLfloat s1 = texCoords.x1;
    GLfloat v1 = texCoords.y1;
    GLfloat s2 = texCoords.x2;
    GLfloat v2 = texCoords.y1;
    GLfloat s3 = texCoords.x2;
    GLfloat v3 = texCoords.y2;
    GLfloat s4 = texCoords.x1;
    GLfloat v4 = texCoords.y2;

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
    buf.id = img->id();
    buf.x1 = x1;
    buf.y1 = y1;
    buf.x2 = x2;
    buf.y2 = y2;
    buf.x3 = x3;
    buf.y3 = y3;
    buf.x4 = x4;
    buf.y4 = y4;

    buf.s1 = s1;
    buf.v1 = v1;
    buf.s2 = s2;
    buf.v2 = v2;
    buf.s3 = s3;
    buf.v3 = v3;
    buf.s4 = s4;
    buf.v4 = v4;

    buf.r = curColor.r;
    buf.g = curColor.g;
    buf.b = curColor.b;
    buf.a = curColor.a;
    imageBuffers.append(buf);

    /*
    glBindTexture(GL_TEXTURE_2D, image->getID());
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(x1, y1);

        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(x2, y2);

        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(x3, y3);

        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(x4, y4);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    */


//        glBindTexture(GL_TEXTURE_2D, img->getID());
//        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

//        glPushMatrix();

//        glTranslatef(x, y, 0.0f);
//        glRotatef(-angle*180.0/M_PI, 0.0f, 0.0f, 1.0f);

//        glEnable(GL_TEXTURE_2D);
//        glBegin(GL_QUADS);
//            glTexCoord2f(0.0f, 1.0f);
//            glVertex2f( - width/2.0f, - height/2.0f);

//            glTexCoord2f(1.0f, 1.0f);
//            glVertex2f( + width/2.0f, - height/2.0f);

//            glTexCoord2f(1.0f, 0.0f);
//            glVertex2f( + width/2.0f, + height/2.0f);

//            glTexCoord2f(0.0f, 0.0f);
//            glVertex2f( - width/2.0f, + height/2.0f);
//        glEnd();
//        glDisable(GL_TEXTURE_2D);

//        glPopMatrix();



        /*
        //view->drawTexture(QRectF(x1, y1, x2, y2), image->getID());
        glBindTexture(GL_TEXTURE_2D, image->getID());
        glEnable(GL_TEXTURE_2D);

        glEnableClientState(GL_VERTEX_ARRAY);
        //glEnableClientState(GL_COLOR_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
        glLineWidth(2.0f);

        GLfloat vertexes[4][2] = {{x1 - x2/2.0f, y1 - y2/2.0f},
                                  {x1 + x2/2.0f, y1 - y2/2.0f},
                                  {x1 + x2/2.0f, y1 + y2/2.0f},
                                  {x1 - x2/2.0f, y1 + y2/2.0f}};
        GLfloat colors[] = {1.0, 0.0, 0.0,
                            1.0, 0.0, 0.0,
                            1.0, 1.0, 0.0,
                            1.0, 0.0, 0.0};
        GLfloat texture_coords[] = {0, 0, 1, 0, 1, 1, 0, 1};

        glVertexPointer(2, GL_FLOAT, 0, vertexes);
        glTexCoordPointer(2, GL_FLOAT, 0, texture_coords);
        //glColorPointer(3, GL_FLOAT, 0, colors);

        glDrawArrays(GL_QUADS, 0, 4);

        glDisableClientState(GL_VERTEX_ARRAY);
        //glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glDisable(GL_TEXTURE_2D);
        */
}

void Graphic::line(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
    if (lineBuffers.size() >= INT_MAX || imageBuffers.size() > 0) {
        flush();
    }

    LineBuffer buf;
    buf.x1 = x1;
    buf.y1 = y1;
    buf.x2 = x2;
    buf.y2 = y2;
    buf.r = curColor.r;
    buf.g = curColor.g;
    buf.b = curColor.b;
    buf.a = curColor.a;
    lineBuffers += buf;

//    glColor4f(curColor.r, curColor.g, curColor.b, curColor.a);
//    glLineWidth(lineWidth_);
//    glBegin(GL_LINES);
//        glVertex2f(x1, y1);
//        glVertex2f(x2, y2);
//    glEnd();
}

void Graphic::line(Image *img, GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    double k = lineParts_;

    if (lineParts_ == 0)
        k = fmax(fabs(dx), fabs(dy));

    for(int i=0; i<k; i++){
        image(img, x1 + dx*(i/k), y1 + dy*(i/k), lineWidth_, lineWidth_);
    }
}

void Graphic::bezier(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4)
{
    double xPrev = x1;
    double yPrev = y1;
    double k = lineParts_;

    if (lineParts_ == 0)
        k = 100;

    for(int i=1; i<=k; i++){
        double t = i / k;
        double x = pow(1.0-t, 3)*x1 + 3*pow(1.0-t, 2)*t*x2 + 3*(1.0-t)*pow(t, 2)*x3 + pow(t, 3)*x4;
        double y = pow(1.0-t, 3)*y1 + 3*pow(1.0-t, 2)*t*y2 + 3*(1.0-t)*pow(t, 2)*y3 + pow(t, 3)*y4;
        line(xPrev, yPrev, x, y);
        xPrev = x;
        yPrev = y;
    }
}

void Graphic::bezier(Image *img, GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2,
                                 GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4)
{
    double xPrev = x1;
    double yPrev = y1;
    double k = lineParts_;

    if (lineParts_ == 0)
        k = 100;

    for(int i=1; i<=k; i++){
        double t = i / k;
        double x = pow(1.0-t, 3)*x1 + 3*pow(1.0-t, 2)*t*x2 + 3*(1.0-t)*pow(t, 2)*x3 + pow(t, 3)*x4;
        double y = pow(1.0-t, 3)*y1 + 3*pow(1.0-t, 2)*t*y2 + 3*(1.0-t)*pow(t, 2)*y3 + pow(t, 3)*y4;
        image(img, x+(xPrev-x)/2.0, y+(yPrev-y)/2.0,
              Tools::distance(xPrev, yPrev, x, y), lineWidth_,
              Tools::angle(xPrev, yPrev, x, y));
        xPrev = x;
        yPrev = y;
    }
}

void Graphic::flush()
{
    flushImage();
    flushLine();
}

void Graphic::flushImage()
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

        coords[i*8+0] = buf.s1;
        coords[i*8+1] = buf.v1;
        coords[i*8+2] = buf.s2;
        coords[i*8+3] = buf.v2;
        coords[i*8+4] = buf.s3;
        coords[i*8+5] = buf.v3;
        coords[i*8+6] = buf.s4;
        coords[i*8+7] = buf.v4;
    }

    glBindTexture(GL_TEXTURE_2D, imageBuffers.at(0).id);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    //GLfloat envColor[4] = {1, 1, 1, 0};
    //glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, envColor);

    //glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
    //GLfloat envColor[4] = {curColor.r, curColor.g, curColor.b, curColor.a};
    //glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, envColor);

    glEnable(GL_TEXTURE_2D);

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

void Graphic::flushLine()
{
    int n = lineBuffers.size();

    if (n==0)
        return;

    GLfloat *vertexes = new GLfloat[2*2*n];
    GLfloat *colors = new GLfloat[2*4*n];

    for (int i=0; i<n; i++) {
        const LineBuffer &buf = lineBuffers.at(i);

        vertexes[i*4+0] = buf.x1;
        vertexes[i*4+1] = buf.y1;
        vertexes[i*4+2] = buf.x2;
        vertexes[i*4+3] = buf.y2;

        colors[i*8+0] = buf.r;
        colors[i*8+1] = buf.g;
        colors[i*8+2] = buf.b;
        colors[i*8+3] = buf.a;
        colors[i*8+4] = buf.r;
        colors[i*8+5] = buf.g;
        colors[i*8+6] = buf.b;
        colors[i*8+7] = buf.a;
    }

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(2, GL_FLOAT, 0, vertexes);
    glColorPointer(4, GL_FLOAT, 0, colors);

    glDrawArrays(GL_LINES, 0, 2*n);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    lineBuffers.clear();
    delete [] vertexes;
    delete [] colors;
}

