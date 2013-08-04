#include "view.h"

#include <QDebug>

View::View(QGLFormat &format, QWidget *parent)
     : QGLWidget(format, parent)
{
    setWindowTitle("Scenery View");
    emptyScene = new EmptyScene();
    setScene(emptyScene);

    show();

    fpsRest = 0;
    fpsFrames = 0;
    fpsResult = 0;
    fpsTime.start();
}

View::~View()
{
    delete emptyScene;
}

void View::setScene(SScene *scene)
{
    this->scene = scene;
    scene->setupEvent(this);
    scene->resizeEvent();
}

void View::bindImage(Image *image)
{
    GLuint id = bindTexture(QPixmap(image->name()), GL_TEXTURE_2D);
    image->_setId(id);
}

int View::time()
{
    return 0;
}

int View::dtime()
{
    return 0;
}

void View::initializeGL()
{
    initializeGLFunctions();

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
    graphic()->setViewSize(width, height);

    glViewport(0, 0, (GLint)width, (GLint)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, width, height, 0, 1, -1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    scene->resizeEvent();
}

void View::paintGL()
{
    glLoadIdentity();
    scene->paintEvent();
    graphic()->flush();

    GLenum errCode = glGetError();
    if (errCode != GL_NO_ERROR) {
        qDebug() << "OpenGL Error!";
    }

    // Counting FPS
    fpsFrames++;
    int fpsElapsed = fpsTime.elapsed();
    if (fpsElapsed + fpsRest > 999) {
        fpsRest = fpsElapsed + fpsRest - 999;
        fpsResult = fpsFrames;
        fpsFrames = 0;
        fpsTime.restart();
    }
}
