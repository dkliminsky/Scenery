#include "controlbuttonwidget.h"

ControlButtonWidget::ControlButtonWidget(Scene *scene, ControlButton *control, QWidget *parent) :
    QWidget(parent)
{
    this->scene = scene;
    this->control = control;
    this->buttons = control->getButtons();
    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->setContentsMargins(0, 0, 0, 0);

    if (buttons.size() > 0) {
        QPushButton *pushButton = new QPushButton(buttons.at(0).name);
        connect(pushButton, SIGNAL(clicked()), SLOT(button0()));
        hLayout->addWidget(pushButton);
    }

    if (buttons.size() > 1) {
        QPushButton *pushButton = new QPushButton(buttons.at(1).name);
        connect(pushButton, SIGNAL(clicked()), SLOT(button1()));
        hLayout->addWidget(pushButton);
    }

    if (buttons.size() > 2) {
        QPushButton *pushButton = new QPushButton(buttons.at(2).name);
        connect(pushButton, SIGNAL(clicked()), SLOT(button2()));
        hLayout->addWidget(pushButton);
    }

    if (buttons.size() > 3) {
        QPushButton *pushButton = new QPushButton(buttons.at(3).name);
        connect(pushButton, SIGNAL(clicked()), SLOT(button3()));
        hLayout->addWidget(pushButton);
    }

    if (buttons.size() > 4) {
        QPushButton *pushButton = new QPushButton(buttons.at(4).name);
        connect(pushButton, SIGNAL(clicked()), SLOT(button4()));
        hLayout->addWidget(pushButton);
    }

    if (buttons.size() > 5) {
        QPushButton *pushButton = new QPushButton(buttons.at(5).name);
        connect(pushButton, SIGNAL(clicked()), SLOT(button5()));
        hLayout->addWidget(pushButton);
    }

    this->setLayout(hLayout);
}

void ControlButtonWidget::button0()
{
    scene->action(control->getButtons().at(0).id);
}

void ControlButtonWidget::button1()
{
    scene->action(control->getButtons().at(1).id);
}

void ControlButtonWidget::button2()
{
    scene->action(control->getButtons().at(2).id);
}

void ControlButtonWidget::button3()
{
    scene->action(control->getButtons().at(3).id);
}

void ControlButtonWidget::button4()
{
    scene->action(control->getButtons().at(4).id);
}

void ControlButtonWidget::button5()
{
    scene->action(control->getButtons().at(5).id);
}
