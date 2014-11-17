#ifndef CONTROLWIDGETS_H
#define CONTROLWIDGETS_H

#include "nodes/controls/icontrol.h"

#include "controlintwidget.h"
#include "controldoublewidget.h"
#include "controlboolwidget.h"

QWidget *control_widget_factory(IControl *control);


#endif // CONTROLWIDGETS_H
