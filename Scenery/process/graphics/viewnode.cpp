#include "viewnode.h"
#include "scene.h"

ViewNode::ViewNode(QGLFormat &format, QWidget *parent)
     : QGLWidget(format, parent)
{
    METHOD_BEGIN

    setWindowTitle("Scenery View");
    setScene(&emptyScene);
    show();

    METHOD_END
}

ViewNode::~ViewNode()
{

}

void ViewNode::setScene(IScene *scene)
{
    this->scene = scene;
    scene->setupEvent(this);
    scene->resizeEvent();
}

void ViewNode::run()
{
    updateGL();
}

void ViewNode::initializeGL()
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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // При фильтрации игнорируются тексели,
    // выходящие за границу текстуры для s и t координаты
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}

void ViewNode::resizeGL(int width, int height)
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

void ViewNode::paintGL()
{
    glLoadIdentity();
    scene->paintEvent();
    graphic()->flush();

    GLenum errCode = glGetError();
    if (errCode != GL_NO_ERROR) {
        qDebug() << "OpenGL Error!";
    }

    // Пометим все данные как не обновленные, на случай того,
    // что до следующего цикла графики они не успеют обновиться
//    for (int i=0; i<_datas.size(); i++) {
//        _datas.at(i)->setIsUpdate(false);
//    }
}
