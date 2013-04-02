#include "view.h"

#include <QDebug>


View::View()
{
    timePaint = 0;
    prevTimePaint = 0;
    differenceTimePaint = 0;

    scene = 0;
    fpsRest = 0;
    fpsFrames = 0;
    fpsResult = 0;
    fpsTime.start();
    show();
}

void View::setScene(IScene *scene)
{
    this->scene = scene;
    timeScene.restart();
    timePaint = timeScene.elapsed();
    scene->setupEvent(this);
    scene->resizeEvent(width, height);
}

int View::getTimeScene()
{
    return timeScene.elapsed();
}

int View::getPaintTimeScene()
{
    return differenceTimePaint;
}

void View::initializeGL()
{
    initializeGLFunctions();

    GLint texMaxSize;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &texMaxSize);
    //qDebug() << "Max texture size:" << texMaxSize;

    glShadeModel(GL_SMOOTH);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glDisable(GL_DEPTH_TEST);

    // Задаём фильтрацию вблизи и вдали:
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // Задаём фильтрацию вблизи и в дали:
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // При фильтрации игнорируются тексели,
    // выходящие за границу текстуры для s и t координаты
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
}

void View::resizeGL(int width, int height)
{
    this->width   = width;
    this->height  = height;

    glViewport(0, 0, (GLint)width, (GLint)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, width, height, 0, 1, -1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (scene)
        scene->resizeEvent(width, height);
}

void View::paintGL()
{
    prevTimePaint = timePaint;
    timePaint = timeScene.elapsed();
    differenceTimePaint = timePaint - prevTimePaint;

    if (scene)
        scene->paintEvent();

    fpsFrames++;
    int fpsElapsed = fpsTime.elapsed();

    if (fpsElapsed + fpsRest > 999) {
        fpsRest = fpsElapsed + fpsRest - 999;
        fpsResult = fpsFrames;
        fpsFrames = 0;
        fpsTime.restart();
    }

    GLenum errCode = glGetError();
    if (errCode != GL_NO_ERROR) {
        qDebug() << "OpenGL Error!";
    }
}
