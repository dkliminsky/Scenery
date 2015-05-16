#include "controlstringwidget.h"

ControlStringWidget::ControlStringWidget(ControlString *control,
                                         QWidget *parent) :
    QComboBox(parent)
{
    this->control = control;

    if (control->list().contains(control->value()))
        this->addItems(control->list());
    else {
        this->addItem(control->value());
        this->addItems(control->list());
    }

    connect(this, SIGNAL(currentIndexChanged(int)), SLOT(change()));
    connect(control, &Control::updateData, this, &ControlStringWidget::update);
}

void ControlStringWidget::change()
{
    control->value() = this->currentText();
}

void ControlStringWidget::update()
{
    int i = this->findText(control->value());
    if (i >= 0)
        this->setCurrentIndex(i);
    else {
        this->addItem(control->value());
        this->setCurrentIndex(this->count());
    }
}
