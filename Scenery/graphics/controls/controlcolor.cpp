#include "controlcolor.h"

#include <QDebug>

ControlColor::ControlColor(Color &color) :
    color(color)
{
    spinR = new QDoubleSpinBox();
    spinR->setRange(0, 1);
    spinR->setDecimals(2);
    spinR->setSingleStep(0.05);
    spinR->setValue(color.r);

    spinG = new QDoubleSpinBox();
    spinG->setRange(0, 1);
    spinG->setDecimals(2);
    spinG->setSingleStep(0.05);
    spinG->setValue(color.g);

    spinB = new QDoubleSpinBox();
    spinB->setRange(0, 1);
    spinB->setDecimals(2);
    spinB->setSingleStep(0.05);
    spinB->setValue(color.b);

    spinA = new QDoubleSpinBox();
    spinA->setRange(0, 1);
    spinA->setDecimals(2);
    spinA->setSingleStep(0.05);
    spinA->setValue(color.a);

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
    connect(button, SIGNAL(clicked()), SLOT(slotColorDialog()));
    connect(colorDialog, SIGNAL(currentColorChanged(QColor)), SLOT(slotColorDialogSelected(QColor)));

    isSlotOn = true;
}

void ControlColor::updateData()
{
    isSlotOn = false;
    spinR->setValue(color.r);
    spinG->setValue(color.g);
    spinB->setValue(color.b);
    spinA->setValue(color.a);
    isSlotOn = true;
}

void ControlColor::setData(QString &data)
{
}

void ControlColor::slotChange()
{
    if (isSlotOn) {
        color.r = spinR->value();
        color.g = spinG->value();
        color.b = spinB->value();
        color.a = spinA->value();
    }
}

void ControlColor::slotColorDialog()
{
    QColor c(color.r*255.0, color.g*255.0, color.b*255.0, color.a*255.0);
    colorDialog->setCurrentColor(c);
    colorDialog->show();
}

void ControlColor::slotColorDialogSelected(QColor c)
{
    qDebug() << "Color";
    color.r = c.red() / 255.0;
    color.g = c.green() / 255.0;
    color.b = c.blue() / 255.0;
    color.a = c.alpha() / 255.0;
    updateData();
}
