#ifndef CONTROLCOLOR_H
#define CONTROLCOLOR_H

#include "../elements/color.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QDoubleSpinBox>

class ControlColor : public QWidget
{
    Q_OBJECT
public:
    explicit ControlColor(Color &color);

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
