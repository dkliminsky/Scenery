#ifndef VIEW_H
#define VIEW_H

#include <QGLWidget>
#include <QGLFunctions>
#include <QTime>

#include "nodes/node.h"
#include "iscene.h"
#include "graphic.h"


class ViewNode : public Node, public QGLWidget, protected QGLFunctions
{
public:
    ViewNode(QWidget *parent = 0);
    ~ViewNode();
    virtual const QString name() { return "View"; }
    virtual const QString tooltip() { return "View graphics"; }

    void setScene(IScene *scene);
    Graphic *graphic() { return &_graphic; }

protected:
    void timerEvent(QTimerEvent *);

    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

private:
    GLint width;
    GLint height;
    IScene *scene;
    IScene emptyScene;
    Graphic _graphic;
};

#endif // VIEW_H
