#include "controlboolwidget.h"

ControlBoolWidget::ControlBoolWidget(ControlBool *controlBool, QWidget *parent) :
    QCheckBox(parent)
{
    this->control = controlBool;
    update();
    connect(this, &QCheckBox::clicked, this, &ControlBoolWidget::change);
}

void ControlBoolWidget::change()
{
    control->value() = this->isChecked();
}

void ControlBoolWidget::update()
{
    this->setChecked(control->value());
}
