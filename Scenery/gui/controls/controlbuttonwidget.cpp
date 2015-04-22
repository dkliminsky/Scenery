#include "controlbuttonwidget.h"

ControlButtonWidget::ControlButtonWidget(ControlButton *control, QWidget *parent) :
    QWidget(parent)
{
    this->control = control;
    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->setContentsMargins(0, 0, 0, 0);

    QPushButton *pushButton = new QPushButton(control->name());
    connect(pushButton, SIGNAL(clicked()), SLOT(button()));
    hLayout->addWidget(pushButton);

    this->setLayout(hLayout);
}

void ControlButtonWidget::button()
{
    control->provider->signal(control->id);
}

