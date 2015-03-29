#include "controlwidgets.h"

#include <QScrollArea>
#include <QScrollBar>


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
        return new ControlButtonWidget(static_cast<ControlButton *>(control));
    case IControl::ControlGroup:
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
        IControl *control = controls->at(i);
        QWidget *widget = control_widget_factory(control);

        if (control->type() == IControl::ControlGroup) {
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
            }
            gridLayout->addWidget(new QLabel(control->name()), n, 0);
            gridLayout->addWidget(widget, n, 1);
            layout->addLayout(gridLayout);
            n++;
        }
    }
    //gridLayout->setRowStretch(gridLayout->count()-1, 1);


    QWidget *widget = new QWidget();
    widget->setLayout(layout);

    QScrollArea *scroll = new QScrollArea();
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scroll->setWidget(widget);
    scroll->setFixedWidth(widget->width() + 20);
    return scroll;
}
