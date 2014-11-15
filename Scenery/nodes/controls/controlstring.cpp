#include "controlstring.h"

ControlString::ControlString(QString &data, QString name,
                             QStringList list) :
    IControl(IControl::ControlString, name), _data(data)
{
    _list = list;
}

void ControlString::set(QString &data)
{
    _data = data;
}

QString ControlString::get()
{
    return _data;
}
