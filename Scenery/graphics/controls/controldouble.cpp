#include "controldouble.h"
#include <math.h>

ControlDouble::ControlDouble(double &data, double min, double max, int precision) :
    data(data)
{
    this->setRange(min, max);
    this->setDecimals(precision);
    this->setSingleStep( 1.0/pow(10, precision) );
    this->setValue(data);

    connect(this, SIGNAL(valueChanged(double)),  SLOT(slotChange()));
}

void ControlDouble::setData(QString &data)
{
}

void ControlDouble::slotChange()
{
    data = this->value();
}
