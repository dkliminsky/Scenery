#include "actionbuttonwidget.h"

ActionButtonWidget::ActionButtonWidget(Scene *scene, int id, QWidget *parent) :
    QWidget(parent)
{
    this->scene = scene;
    this->id = id;

    pushButton = new QPushButton("Send");
    connect(pushButton, SIGNAL(clicked()), SLOT(signal()));

    hLayout = new QHBoxLayout();
    hLayout->setContentsMargins(0, 0, 0, 0);
    hLayout->addWidget(pushButton);

    this->setLayout(hLayout);
}

void ActionButtonWidget::signal()
{
    scene->action(id);
}

