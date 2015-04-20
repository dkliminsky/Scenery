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

QWidget *make_controls_widget(Controls *controls)
{
    QVBoxLayout *layout = new QVBoxLayout();

    QGridLayout *gridLayout = nullptr;
    ControlGroupWidget *groupWidget = nullptr;
    int n = 0;
    for(int i=0; i<controls->size(); i++) {
        Control *control = controls->at(i);
        QWidget *widget = control_widget_factory(control);

        if (control->type() == Control::ControlGroup) {
            gridLayout = new QGridLayout();
            gridLayout->setContentsMargins(5, 8, 5, 5);

            groupWidget = static_cast<ControlGroupWidget *>(widget);
            groupWidget->setLayout(gridLayout);
            layout->addWidget(groupWidget);
            n = 0;
        }
        else {
            if (!gridLayout) {
                gridLayout = new QGridLayout();
                gridLayout->setContentsMargins(5, 8, 5, 5);
                layout->addLayout(gridLayout);
            }
            gridLayout->addWidget(new QLabel(control->name()), n, 0);
            gridLayout->addWidget(widget, n, 1);
            n++;
        }
    }
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
