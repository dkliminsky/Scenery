#ifndef VIEW_H
#define VIEW_H

#include <QGLWidget>
#include <QGLFunctions>
#include <QTime>

#include "sscene.h"
#include "graphic.h"
#include "process/processdata.h"
#include "emptyscene.h"
#include "elements/color.h"

class View : public QGLWidget, protected QGLFunctions
{
public:
    View(QGLFormat &format, QWidget *parent = 0);
    ~View();
    void setScene(SScene *scene);
    ProcessDatas *datas()   { return &_datas; }
    Utils        *utils()   { return &_utils; }
    Graphic      *graphic() { return &_graphic; }

    void bindImage(Image *image);
    int time();
    int dtime();
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

    ProcessDatas _datas;
    Utils _utils;
    Graphic _graphic;

    QTime timer;

    QTime fpsTime;
    int fpsRest;
    int fpsFrames;
    int fpsResult;
};

#endif // VIEW_H
