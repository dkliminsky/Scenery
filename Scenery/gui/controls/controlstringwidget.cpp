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

//    connect(this, &QComboBox::currentIndexChanged,
//            this, &ControlStringWidget::change);
    connect(this, SIGNAL(currentIndexChanged(int)), SLOT(change()));
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
