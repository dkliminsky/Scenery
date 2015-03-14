#include "scene.h"

#include "tools.h"
#include "nodes/controls/controls.h"


Scene::Scene()
{

}

Scene::~Scene()
{

}

void Scene::control(int &x, QString description, int min, int max, int step)
{
    _controls += new ControlInt(x, description, min, max, step);
}

void Scene::control(double &x, QString description, double min, double max, int precision)
{
    _controls += new ControlDouble(x, description, min, max, precision);
}

void Scene::control(bool &x, QString description)
{
    _controls += new ControlBool(x, description);
}

void Scene::control(QString &string, QString description, QStringList list)
{
    _controls += new ControlString(string, description, list);
}

