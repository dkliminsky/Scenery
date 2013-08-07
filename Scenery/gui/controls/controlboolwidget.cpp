#include "controlboolwidget.h"

ControlBoolWidget::ControlBoolWidget(ControlBool *controlBool, QWidget *parent) :
    QCheckBox(parent)
{
    this->control = controlBool;
    this->setChecked(control->value());
    connect(this, &QCheckBox::clicked, this, &ControlBoolWidget::slotChange);
}

void ControlBoolWidget::slotChange()
{
    control->value() = this->isChecked();
}
