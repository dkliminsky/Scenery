#include "controlbutton.h"

ControlButton::ControlButton(Scene *scene, int id, QString name) :
    IControl(IControl::ControlButton, name)
{
    this->scene = scene;
    this->id = id;
}
