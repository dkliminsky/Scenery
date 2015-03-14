#include "view.h"

#include "scene.h"
#include "debug.h"

View::View() :
    QOpenGLWindow(QOpenGLWindow::NoPartialUpdate)
{
    METHOD_BEGIN

    _scene = nullptr;

    setTitle("Scenery View");
    show();

    METHOD_END
}

View::~View()
{

}

void View::setScene(Scene *scene)
{
     _scene = scene;
}

void View::initializeGL()
{
    initializeOpenGLFunctions();

    glShadeModel(GL_SMOOTH);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glDisable(GL_DEPTH_TEST);

    // Задаём фильтрацию вблизи и вдали:
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // При фильтрации игнорируются тексели,
    // выходящие за границу текстуры для s и t координаты
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void View::resizeGL(int width, int height)
{
    if (!_scene)
        return;

    _scene->_widthView = width;
    _scene->_heightView = height;

    QPainter p(this);
    _scene->_painter = &p;
    _scene->resize();

    glScalef((GLfloat)width, (GLfloat)height, 1.0f);

    glViewport(0, 0, (GLint)width, (GLint)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, width, height, 0, 1, -1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void View::paintGL()
{
    if (!_scene)
        return;

    glLoadIdentity();
    
    QPainter p(this);
    _scene->_painter = &p;
    _scene->paint();

    GLenum errCode = glGetError();
    if (errCode != GL_NO_ERROR) {
        qDebug() << "OpenGL Error!";
    }
}
