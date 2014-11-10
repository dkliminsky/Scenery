#include "controlcolorwidget.h"

ControlColorWidget::ControlColorWidget(ControlColor *control){
    this->control = control;

    spinR = new QDoubleSpinBox();
    spinR->setRange(0, 1);
    spinR->setDecimals(2);
    spinR->setSingleStep(0.05);

    spinG = new QDoubleSpinBox();
    spinG->setRange(0, 1);
    spinG->setDecimals(2);
    spinG->setSingleStep(0.05);

    spinB = new QDoubleSpinBox();
    spinB->setRange(0, 1);
    spinB->setDecimals(2);
    spinB->setSingleStep(0.05);

    spinA = new QDoubleSpinBox();
    spinA->setRange(0, 1);
    spinA->setDecimals(2);
    spinA->setSingleStep(0.05);

    button = new QPushButton("Change");
    colorDialog = new QColorDialog(this);
    colorDialog->setOptions(QColorDialog::ShowAlphaChannel);

    hLayout = new QHBoxLayout();
    hLayout->setContentsMargins(0, 0, 0, 0);
    hLayout->addWidget(spinR);
    hLayout->addWidget(spinG);
    hLayout->addWidget(spinB);
    hLayout->addWidget(spinA);
    hLayout->addWidget(button);

    this->setLayout(hLayout);

    connect(spinR, SIGNAL(valueChanged(double)),  SLOT(slotChange()));
    connect(spinG, SIGNAL(valueChanged(double)),  SLOT(slotChange()));
    connect(spinB, SIGNAL(valueChanged(double)),  SLOT(slotChange()));
    connect(spinA, SIGNAL(valueChanged(double)),  SLOT(slotChange()));
    connect(button, SIGNAL(clicked()), SLOT(showColorDialog()));
    connect(colorDialog, SIGNAL(currentColorChanged(QColor)),
            SLOT(changeColor(QColor)));

    update();
}

void ControlColorWidget::slotChange()
{
    if (isSlotChangeOn) {
        control->value().r = spinR->value();
        control->value().g = spinG->value();
        control->value().b = spinB->value();
        control->value().a = spinA->value();
    }
}

void ControlColorWidget::update()
{
    isSlotChangeOn = false;
    spinR->setValue(control->value().r);
    spinG->setValue(control->value().g);
    spinB->setValue(control->value().b);
    spinA->setValue(control->value().a);
    isSlotChangeOn = true;
}

void ControlColorWidget::showColorDialog()
{
    QColor c(control->value().r*255.0, control->value().g*255.0,
             control->value().b*255.0, control->value().a*255.0);
    colorDialog->setCurrentColor(c);
    colorDialog->show();
}

void ControlColorWidget::changeColor(QColor c)
{
    control->value().r = c.red() / 255.0;
    control->value().g = c.green() / 255.0;
    control->value().b = c.blue() / 255.0;
    control->value().a = c.alpha() / 255.0;
    update();
}
