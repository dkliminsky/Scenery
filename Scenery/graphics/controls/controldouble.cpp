#include "controldouble.h"
#include <math.h>

ControlDouble::ControlDouble(double &data, QString name, double min, double max, int precision) :
    IControl(name), data(data)
{
    this->setRange(min, max);
    this->setDecimals(precision);
    this->setSingleStep( 1.0/pow(10, precision) );

    connect(this, SIGNAL(valueChanged(double)),  SLOT(slotChange()));

    updateData();
}

void ControlDouble::updateData()
{
    this->setValue(data);
}

void ControlDouble::setData(QString &data)
{
    this->data = QString(data).toDouble();
}

QString ControlDouble::getData()
{
    return QString().setNum(data);
}

void ControlDouble::slotChange()
{
    data = this->value();
}
