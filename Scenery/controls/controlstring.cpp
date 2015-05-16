#include "controlstring.h"

ControlString::ControlString(QString &data, QString name,
                             QStringList list) :
    Control(Control::ControlString, name), _data(data)
{
    _list = list;
}

void ControlString::set(QString &data)
{
    _data = data;

    emit updateData();
}

QString ControlString::get()
{
    return _data;
}
