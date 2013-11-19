#include "controlstringwidget.h"
#include <QHBoxLayout>


ControlStringWidget::ControlStringWidget(ControlString *control)
{
    this->control = control;

    comboBox = new QComboBox();

    if (control->list().contains(control->value()))
        comboBox->addItems(control->list());
    else {
        comboBox->addItem(control->value());
        comboBox->addItems(control->list());
    }

    QHBoxLayout *layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(comboBox);
    this->setLayout(layout);

//    connect(this, &QComboBox::currentIndexChanged,
//            this, &ControlStringWidget::change);
    connect(comboBox, SIGNAL(currentIndexChanged(int)), SLOT(slotChange()));
}

void ControlStringWidget::slotChange()
{
    control->value() = comboBox->currentText();
}

void ControlStringWidget::update()
{
    int i = comboBox->findText(control->value());
    if (i >= 0)
        comboBox->setCurrentIndex(i);
    else {
        comboBox->addItem(control->value());
        comboBox->setCurrentIndex(comboBox->count());
    }
}
