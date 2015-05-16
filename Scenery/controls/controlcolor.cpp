#include "controlcolor.h"

ControlColor::ControlColor(Color &color, QString name) :
    Control(Control::ControlColor, name), _color(color)
{
}

void ControlColor::set(QString &color)
{
    QStringList list = color.split(",");
    if (list.size() == 4) {
        _color.r = list.at(0).toFloat();
        _color.g = list.at(1).toFloat();
        _color.b = list.at(2).toFloat();
        _color.a = list.at(3).toFloat();
    }

    emit updateData();
}

QString ControlColor::get()
{
    return QString().setNum(_color.r) + "," + QString().setNum(_color.g) + "," +
           QString().setNum(_color.b) + "," + QString().setNum(_color.a);
}
