#ifndef CONTROLDOUBLE_H
#define CONTROLDOUBLE_H

#include "icontrol.h"

class ControlDouble : public IControl
{
public:
    ControlDouble(double &data, QString name,
                  double min=0, double max=999, int precision=1);

    void set(QString &data);
    QString get();

    double &value() { return _data; }
    double min() { return _min; }
    double max() { return _max; }
    double precision() { return _precision; }

private:
    double &_data;
    double _min;
    double _max;
    double _precision;

};

#endif // CONTROLDOUBLE_H
