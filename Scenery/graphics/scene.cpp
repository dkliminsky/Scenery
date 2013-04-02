#include "scene.h"
#include <QtGlobal>

Scene::Scene()
{
    setProcessCount(1);
}

void Scene::setProcessCount(int n)
{
    seqAreasVector.resize(n);
    areasVector.resize(n);
    widthVector.resize(n);
    heightVector.resize(n);
}

void Scene::setupEvent(void *view)
{
    this->view = static_cast<View *>(view);
    sceneChanged();
    setup();
}

void Scene::paintEvent()
{
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

