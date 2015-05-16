#include "controldoublewidget.h"
#include <math.h>

ControlDoubleWidget::ControlDoubleWidget(ControlDouble *control, QWidget *parent) :
    QDoubleSpinBox(parent)
{
    this->control = control;

    this->setRange(control->min(), control->max());
    this->setDecimals(control->precision());
    this->setSingleStep( 1.0/pow(10, control->precision()) );

    update();

//    connect(this, &QDoubleSpinBox::valueChanged,
//            this, &ControlDoubleWidget::change);
    connect(this, SIGNAL(valueChanged(double)), SLOT(change()));
    connect(control, &Control::updateData, this, &ControlDoubleWidget::update);
}

void ControlDoubleWidget::change()
{
    control->value() = this->value();
}

void ControlDoubleWidget::update()
{
    this->setValue(control->value());
}
