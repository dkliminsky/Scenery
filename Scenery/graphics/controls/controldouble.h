#ifndef CONTROLDOUBLE_H
#define CONTROLDOUBLE_H

#include "icontrol.h"

#include <QDoubleSpinBox>

class ControlDouble : public QDoubleSpinBox, public IControl
{
    Q_OBJECT
public:
    explicit ControlDouble(double &data, double min, double max, int precision);
    void setData(QString &data) { ; }
    QString &getData() { return *(new QString("")); }


private:
    double &data;

public slots:
    void slotChange();

};

#endif // CONTROLDOUBLE_H
