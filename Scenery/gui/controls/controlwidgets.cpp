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
        return new ControlStringWidget(static_cast<ControlString *>(control));
    case IControl::ControlColor:
        return new ControlColorWidget(static_cast<ControlColor *>(control));
    case IControl::ControlImage:
        return new QWidget;
    case IControl::ControlButton:
        return new QWidget;
    default:
        return new QWidget;
    }
}

QLayout *make_controls_layout(Controls *controls)
{
    QGridLayout *layout = new QGridLayout();
    layout->setContentsMargins(0, 0, 0, 0);

    for(int i=0; i<controls->size(); i++) {
        IControl *control = controls->at(i);
        layout->addWidget(new QLabel(control->name()), i, 0);
        layout->addWidget(control_widget_factory(control), i, 1);
    }
    layout->setRowStretch(layout->count()-1, 1);
    return layout;
}
