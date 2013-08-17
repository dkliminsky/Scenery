#ifndef VIEW_H
#define VIEW_H

#include <QGLWidget>
#include <QGLFunctions>
#include <QTime>

#include "sscene.h"
#include "graphic.h"
#include "node.h"
#include "emptyscene.h"
#include "elements/color.h"

typedef QVector<Node *> Datas;

class View : public QGLWidget, protected QGLFunctions
{
public:
    View(QGLFormat &format, QWidget *parent = 0);
    ~View();
    void setScene(SScene *scene);
    Datas   *datas()   { return &_datas; }
    Utils   *utils()   { return &_utils; }
    Graphic *graphic() { return &_graphic; }

    int time();
    int dtime() { return timeStep; }
    int fps() { return fpsResult; }

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

private:
    GLint width;
    GLint height;
    SScene *scene;
    SScene *emptyScene;

    Datas _datas;
    Utils _utils;
    Graphic _graphic;

    int timeLast;
    int timeStep;
    QTime timer;

    QTime fpsTime;
    int fpsRest;
    int fpsFrames;
    int fpsResult;
};

#endif // VIEW_H
