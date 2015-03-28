#ifndef VIEW_H
#define VIEW_H

#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QTime>

#include "scene.h"


class View : public QOpenGLWindow, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    View();
    ~View();

    Scene *scene() { return _scene; }
    void setScene(Scene *scene);

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

private:
    Scene *_scene;
    int _width;
    int _height;

    QTime timer;
    int timeLast;
    int timeStep;

};

#endif // VIEW_H
