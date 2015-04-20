#include "controldouble.h"

ControlDouble::ControlDouble(double &data, QString name,
                             double min, double max, int precision) :
    Control(Control::ControlDouble, name), _data(data)
{
    _min = min;
    _max = max;
    _precision = precision;
}

void ControlDouble::set(QString &data)
{
    _data = data.toDouble();
}

QString ControlDouble::get()
{
    return QString().number(_data);
}
