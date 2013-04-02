#include "controlint.h"

ControlInt::ControlInt(int &data, int min, int max) :
    data(data)
{
    slider = new QSlider();
    slider->setValue(data);
    slider->setRange(min, max);
    slider->setOrientation(Qt::Horizontal);

    label = new QLabel();
    label->setNum(data);

    hLayout = new QHBoxLayout();
    hLayout->setContentsMargins(0, 0, 0, 0);
    hLayout->addWidget(slider);
    hLayout->addWidget(label);

    this->setLayout(hLayout);

    connect(slider, SIGNAL(valueChanged(int)), SLOT(slotChange()));
}

void ControlInt::slotChange()
{
    data = slider->value();
    label->setNum(data);
}
