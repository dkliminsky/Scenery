#ifndef CONTROLDOUBLE_H
#define CONTROLDOUBLE_H

#include <QDoubleSpinBox>

class ControlDouble : public QDoubleSpinBox
{
    Q_OBJECT
public:
    explicit ControlDouble(double &data, double min, double max, int precision);

private:
    double &data;

public slots:
    void slotChange();

};

#endif // CONTROLDOUBLE_H
