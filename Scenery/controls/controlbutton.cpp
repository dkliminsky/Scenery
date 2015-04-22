#include "controlbutton.h"

ControlButton::ControlButton(ControlProvider *provider, int id, QString name) :
    Control(Control::ControlButton, name)
{
    this->provider = provider;
    this->id = id;
}
