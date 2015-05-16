#include "controlprovider.h"
#include <QDir>
#include <QDebug>
#include "nodes/graphics/elements/elements.h"
#include "debug.h"

ControlProvider::ControlProvider() :
    _baseControl(Control::ControlGroup, "Node Control"),
    lastGroupControl(nullptr),
    curInsertControl(&_baseControl)
{

}

ControlProvider::~ControlProvider()
{

}

void ControlProvider::addControl(int &x, QString name, int min, int max, int step)
{
    insertControl(new ControlInt(x, name, min, max, step));
}

void ControlProvider::addControl(double &x, QString name, double min, double max, int precision)
{
    insertControl(new ControlDouble(x, name, min, max, precision));
}

void ControlProvider::addControl(bool &x, QString name)
{
    insertControl(new ControlBool(x, name));
}

void ControlProvider::addControl(QString &string, QString name, QStringList list)
{
    insertControl(new ControlString(string, name, list));
}

void ControlProvider::addControl(Color &color, QString name)
{
    insertControl(new ControlColor(color, name));
}

void ControlProvider::addControl(Image **image, QString name, QString path, QString file)
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
    insertControl(new ControlImage(image, name, images));
}

void ControlProvider::addControlGroup(QString name)
{
    lastGroupControl = new ControlGroup(name);
    curInsertControl = &_baseControl;
    insertControl(lastGroupControl);
    curInsertControl = lastGroupControl;
}

void ControlProvider::addButton(int id, QString name)
{
    insertControl(new ControlButton(this, id, name));
}

QJsonObject ControlProvider::getControlJson()
{
    return _baseControl.getJson();
}

void ControlProvider::setControlJson(QJsonObject json)
{
    _baseControl.setJson(json);
}

void ControlProvider::insertControl(Control *control)
{
    curInsertControl->insertControl(control);
}
