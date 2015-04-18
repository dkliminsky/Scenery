#include "controlint.h"


ControlInt::ControlInt(int &data, QString name,
                       int min, int max, int step) :
    IControl(IControl::ControlInt, name), _data(data)
{
    _min = min;
    _max = max;
    _step = step;
}

void ControlInt::set(QString &data)
{
    _data = data.toInt();
}

QString ControlInt::get()
{
    return QString().number(_data);
}
