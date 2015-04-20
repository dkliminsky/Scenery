#include "scene.h"

#include "tools.h"

#include <QDir>


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

void Scene::control(Color &color, QString description)
{
    _controls += new ControlColor(color, description);
}


void Scene::control(Image **image, QString description, QString path, QString file)
{
    QDir dir(path);
    if (!dir.exists()) {
        qDebug() << "Path not found:" << path;
        return;
    }

    QStringList filters;
    filters << "*.png" << "*.jpg" << "*.jpeg";
    QStringList list = dir.entryList(filters);

    if (!list.size()) {
        qDebug() << "Images not found in path:" << path;
        return;
    }

    QVector<Image *> images;
    int index = 0;
    for (int i = 0; i < list.size(); i++) {
        QString name = list.at(i);
        Image *imageDir = new Image(path + name);
        images.append(imageDir);

        if (name == file) {
            index = i;
        }
    }

    *image = images.at(index);
    _controls += new ControlImage(image, description, images);
}

void Scene::addControlGroup(QString description)
{
    _controls += new ControlGroup(description);
}

void Scene::button(int id, QString description)
{
    _controls += new ControlButton(this, id, description);
}

