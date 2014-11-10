#include "controldoublewidget.h"
#include <QHBoxLayout>
#include <math.h>

ControlDoubleWidget::ControlDoubleWidget(ControlDouble *control)
{
    this->control = control;

    doubleSpinBox = new QDoubleSpinBox();

    QHBoxLayout *layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(doubleSpinBox);
    this->setLayout(layout);

    doubleSpinBox->setRange(control->min(), control->max());
    doubleSpinBox->setDecimals(control->precision());
    doubleSpinBox->setSingleStep( 1.0/pow(10, control->precision()) );

    update();

//    connect(this, &QDoubleSpinBox::valueChanged,
//            this, &ControlDoubleWidget::change);
    connect(doubleSpinBox, SIGNAL(valueChanged(double)), SLOT(slotChange()));
}

void ControlDoubleWidget::slotChange()
{
    control->value() = doubleSpinBox->value();
}

void ControlDoubleWidget::update()
{
    doubleSpinBox->setValue(control->value());
}
