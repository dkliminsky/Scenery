#include "controlwidgets.h"

#include <QScrollArea>
#include <QScrollBar>


QWidget *control_widget_factory(Control *control)
{
    switch(control->type()) {
    case Control::ControlInt:
        return new ControlIntWidget(static_cast<ControlInt *>(control));
    case Control::ControlDouble:
        return new ControlDoubleWidget(static_cast<ControlDouble *>(control));
    case Control::ControlBool:
        return new ControlBoolWidget(static_cast<ControlBool *>(control));
    case Control::ControlString:
        return new ControlStringWidget(static_cast<ControlString *>(control));
    case Control::ControlColor:
        return new ControlColorWidget(static_cast<ControlColor *>(control));
    case Control::ControlImage:
        return new ControlImageWidget(static_cast<ControlImage *>(control));
    case Control::ControlButton:
        return new ControlButtonWidget(static_cast<ControlButton *>(control));
    case Control::ControlGroup:
        return new ControlGroupWidget(static_cast<ControlGroup *>(control));
    default:
        return new QWidget;
    }
}

QVBoxLayout *make_controls_layout(Controls *controls)
{
    QVBoxLayout *layout = new QVBoxLayout();
    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->setContentsMargins(5, 8, 5, 5);
    layout->addLayout(gridLayout);
    QHashIterator<QString, Control *> i(*controls);
    while (i.hasNext()) {
        i.next();
        Control *control = i.value();
        QWidget *widget = control_widget_factory(control);

        if (control->type() == Control::ControlGroup) {
            //ControlGroupWidget *groupWidget = static_cast<ControlGroupWidget *>(widget);
            widget->setLayout(make_controls_layout(&control->controls()));
            qDebug() << control->controls().count();
            gridLayout->addWidget(widget, control->number(), 1);
        }
        else {
            gridLayout->addWidget(new QLabel(control->name()), control->number(), 0);
            gridLayout->addWidget(widget, control->number(), 1);
        }
    }
    return layout;
}


QWidget *make_controls_widget(Controls *controls)
{
    QVBoxLayout *layout = make_controls_layout(controls);
    layout->addStretch(1);

    QWidget *widget = new QWidget();
    widget->setLayout(layout);

    QScrollArea *scroll = new QScrollArea();
    //scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scroll->setWidget(widget);
    scroll->setWidgetResizable(true);
    //scroll->setMinimumWidth(widget->width() + 20);
    //scroll->setFixedWidth(widget->width() + 20);
    return scroll;
}
