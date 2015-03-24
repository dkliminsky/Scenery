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

QWidget *control_widget_factory(IControl *control);
QLayout *make_controls_layout(Controls *controls);


#endif // CONTROLWIDGETS_H
