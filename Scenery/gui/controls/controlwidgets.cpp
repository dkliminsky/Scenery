#include "controlwidgets.h"


QWidget *control_widget_factory(IControl *control)
{
    switch(control->type()) {
    case IControl::ControlInt:
        return new ControlIntWidget(static_cast<ControlInt *>(control));
    case IControl::ControlDouble:
        return new ControlDoubleWidget(static_cast<ControlDouble *>(control));
    case IControl::ControlBool:
        return new ControlBoolWidget(static_cast<ControlBool *>(control));
    case IControl::ControlString:
        return new QWidget;
    case IControl::ControlColor:
        return new QWidget;
    case IControl::ControlImage:
        return new QWidget;
    case IControl::ControlButton:
        return new QWidget;
    default:
        return new QWidget;
    }
}
