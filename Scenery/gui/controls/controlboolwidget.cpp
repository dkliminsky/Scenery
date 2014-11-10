#include "controlboolwidget.h"
#include <QHBoxLayout>

ControlBoolWidget::ControlBoolWidget(ControlBool *controlBool)
{
    this->control = controlBool;

    checkBox = new QCheckBox();
    QHBoxLayout *layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(checkBox);
    this->setLayout(layout);

    update();
    connect(checkBox, SIGNAL(clicked()), this, SLOT(slotChange()));
}

void ControlBoolWidget::slotChange()
{
    control->value() = checkBox->isChecked();
}

void ControlBoolWidget::update()
{
    checkBox->setChecked(control->value());
}
