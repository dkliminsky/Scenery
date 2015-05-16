#include "controlgroupwidget.h"

ControlGroupWidget::ControlGroupWidget(ControlGroup *control)
{
    setTitle(control->name());
}

ControlGroupWidget::~ControlGroupWidget()
{

}

