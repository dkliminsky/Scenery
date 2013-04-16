#include "controlint.h"

#include <QDebug>

ControlInt::ControlInt(int &data, QString name, int min, int max) :
    IControl(name), data(data)
{
    slider = new QSlider();
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

    updateData();
}

void ControlInt::updateData()
{
    slider->setValue(data);
}

void ControlInt::setData(QString &data)
{
    this->data = QString(data).toInt();
    updateData();
}

QString ControlInt::getData()
{
    return QString().setNum(data);
}

void ControlInt::slotChange()
{
    data = slider->value();
    label->setNum(data);
}
