#include "scene.h"


Scene::Scene()
{

}

Scene::~Scene()
{

}

Port *Scene::input(QString name)
{
    if (!_inputs->contains(name))
        qDebug() << "Not found input" << name << "in scene:" << this->name();
    return _inputs->value(name);
}
