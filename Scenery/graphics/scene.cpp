#include "scene.h"
#include <QtGlobal>

Scene::Scene()
{
    setProcessCount(1);
    firstPaint = true;
}

void Scene::setProcessCount(int n)
{
    seqAreasVector.resize(n);
    areasVector.resize(n);
    widthVector.resize(n);
    heightVector.resize(n);
    contoursVector.resize(n);
}

void Scene::setupEvent(void *view)
{
    qDebug() << "Scene changed!";
    this->view = static_cast<View *>(view);
    sceneChanged();
    firstPaint = true;
}

void Scene::paintEvent()
{
    if (firstPaint) {
        firstPaint = false;
        setup();
    }

    updateSize();
    paint();
    flush();
}

void Scene::resizeEvent(int width, int height)
{
    widthView = width;
    heightView = height;
}

int &Scene::getWidth(int n)
{
    Q_ASSERT(n < widthVector.size());
    return widthVector[n];
}

int &Scene::getHeight(int n)
{
    Q_ASSERT(n < heightVector.size());
    return heightVector[n];
}

Areas &Scene::getAreas(int n)
{
    Q_ASSERT(n < areasVector.size());
    return areasVector[n];
}

SeqAreas &Scene::getSeqAreas(int n)
{
    Q_ASSERT(n < seqAreasVector.size());
    return seqAreasVector[n];
}

Contours &Scene::getContours(int n)
{
    Q_ASSERT(n < contoursVector.size());
    return contoursVector[n];
}

int Scene::time()
{
    Q_ASSERT(view);
    return view->getTimeScene();
}

int Scene::dtime()
{
    Q_ASSERT(view);
    return view->getPaintTimeScene();
}

