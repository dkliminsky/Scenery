#ifndef CONTROLDOUBLE_H
#define CONTROLDOUBLE_H

#include <QDoubleSpinBox>

#include "icontrol.h"

class ControlDouble : public QDoubleSpinBox, public IControl
{
    Q_OBJECT
public:
    explicit ControlDouble(double &data, QString name, double min, double max, int precision);
    void updateData();
    void setData(QString &data);
    QString getData();

private:
    double &data;

public slots:
    void slotChange();

};

#endif // CONTROLDOUBLE_H
