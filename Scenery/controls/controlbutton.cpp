#include "controlbutton.h"

ControlButton::ControlButton(Scene *scene, int id, QString name) :
    Control(Control::ControlButton, name)
{
    this->scene = scene;
    this->id = id;
}
