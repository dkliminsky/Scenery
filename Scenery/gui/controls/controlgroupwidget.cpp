#include "controlgroupwidget.h"

ControlGroupWidget::ControlGroupWidget(ControlGroup *control)
{
    setTitle(control->name());
    //layout = new QHBoxLayout();
    //setLayout(layout);
}

ControlGroupWidget::~ControlGroupWidget()
{

}

void ControlGroupWidget::addControlWidget(QWidget *widget)
{
    layout->addWidget(widget);
}

