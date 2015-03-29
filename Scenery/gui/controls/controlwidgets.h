#ifndef CONTROLWIDGETS_H
#define CONTROLWIDGETS_H

#include "nodes/node.h"
#include "nodes/controls/icontrol.h"

#include "controlintwidget.h"
#include "controldoublewidget.h"
#include "controlboolwidget.h"
#include "controlcolorwidget.h"
#include "controlstringwidget.h"
#include "controlbuttonwidget.h"
#include "controlgroupwidget.h"

QWidget *control_widget_factory(IControl *control);
QWidget *make_controls_widget(Controls *controls);


#endif // CONTROLWIDGETS_H
