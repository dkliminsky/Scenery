#include "controlboolwidget.h"

ControlBoolWidget::ControlBoolWidget(ControlBool *controlBool, QWidget *parent) :
    QCheckBox(parent)
{
    this->control = controlBool;
    update();
    connect(this, &QCheckBox::clicked, this, &ControlBoolWidget::change);
    connect(control, &Control::updateData, this, &ControlBoolWidget::update);
}

void ControlBoolWidget::change()
{
    control->value() = this->isChecked();
}

void ControlBoolWidget::update()
{
    this->setChecked(control->value());
}
