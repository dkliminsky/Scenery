#include "controlbool.h"

ControlBool::ControlBool(bool &data, QString name) :
    Control(Control::ControlBool, name), _data(data)
{

}

void ControlBool::set(QString &data)
{
    if (data.toLower() == "true")
        _data = true;
    else
        _data = false;
}

QString ControlBool::get()
{
    QString data;

    if (_data)
        data = "true";
    else
        data = "false";

    return data;
}
