#include "controlbutton.h"

ControlButton::ControlButton(QString name, QVector<Button> buttons) :
    IControl(IControl::ControlButton, name)
{
    this->buttons = buttons;
}
