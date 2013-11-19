#include "controlintwidget.h"
#include <QHBoxLayout>

ControlIntWidget::ControlIntWidget(ControlInt *control)
{
    this->control = control;

    slider = new QSlider();
    slider->setRange(control->min(), control->max());
    slider->setSingleStep(control->step());
    slider->setOrientation(Qt::Horizontal);

    label = new QLabel();

    hLayout = new QHBoxLayout();
    hLayout->setContentsMargins(0, 0, 0, 0);
    hLayout->addWidget(slider);
    hLayout->addWidget(label);

    this->setLayout(hLayout);

    update();
    connect(slider, SIGNAL(valueChanged(int)),
            this, SLOT(slotChange()));
}

void ControlIntWidget::slotChange()
{
    control->value() = slider->value();
    label->setNum(control->value());
}

void ControlIntWidget::update()
{
    slider->setValue(control->value());
    label->setNum(control->value());
}
