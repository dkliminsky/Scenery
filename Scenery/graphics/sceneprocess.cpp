#include "sceneprocess.h"

SceneProcess::SceneProcess()
{
}

bool SceneProcess::isUpdate()
{
    if (view->datas()->size() > n)
        return view->datas()->at(n)->getIsUpdate();
    else return false;
}

int SceneProcess::width() {
    if (view->datas()->size() > n)
        return view->datas()->at(n)->getWidth();
    else return 0;
}

int SceneProcess::height() {
    if (view->datas()->size() > n)
        return view->datas()->at(n)->getHeight();
    else return 0;
}

Areas &SceneProcess::areas() {
    if (view->datas()->size() > n)
        return view->datas()->at(n)->getAreas();
    else return _areas;
}

SeqAreas &SceneProcess::seqAreas() {
    if (view->datas()->size() > n)
        return view->datas()->at(n)->getSeqAreas();
    else return _seqArea;
}

Contours &SceneProcess::contours() {
    if (view->datas()->size() > n)
        return view->datas()->at(n)->getContours();
    else return _contour;
}

Image *SceneProcess::hit()
{
    if (view->datas()->size() > n && view->datas()->at(n)->getHit()) {
        _hit.set(view->datas()->at(n)->getHit());
    }
    return &_hit;
}

Image *SceneProcess::image() {
    if (view->datas()->size() > n && view->datas()->at(n)->getImage()) {
        _image.set(view->datas()->at(n)->getImage());
    }
    return &_image;
}

void SceneProcess::command(QString name)
{
    if (view->datas()->size() > n) {
        view->datas()->at(n)->setCommand(name);
    }
}
