#include "controlbutton.h"

ControlButton::ControlButton(IScene *scene, int id, QString text)
{
    this->scene = scene;
    this->id = id;
    this->setText(text);

    connect(this, SIGNAL(clicked()), SLOT(slotPush()));
}

void ControlButton::slotPush()
{
    scene->pushButton(id);
}

