#ifndef CONTROLCOLOR_H
#define CONTROLCOLOR_H

#include "icontrol.h"
#include "../elements/color.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QDoubleSpinBox>

class ControlColor : public QWidget, public IControl
{
    Q_OBJECT
public:
    explicit ControlColor(Color &color);
    void setData(QString &data);
    QString &getData() { return *(new QString("")); }


private:
    Color &color;
    QHBoxLayout *hLayout;
    QDoubleSpinBox *spinR;
    QDoubleSpinBox *spinG;
    QDoubleSpinBox *spinB;
    QDoubleSpinBox *spinA;

public slots:
    void slotChange();
};

#endif // CONTROLCOLOR_H
