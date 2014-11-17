#include "controlintwidget.h"

ControlIntWidget::ControlIntWidget(ControlInt *control, QWidget *parent) :
    QWidget(parent)
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
    connect(slider, &QSlider::valueChanged,
              this, &ControlIntWidget::change);
}

void ControlIntWidget::change()
{
    control->value() = slider->value();
    label->setNum(control->value());
}

void ControlIntWidget::update()
{
    slider->setValue(control->value());
    label->setNum(control->value());
}
