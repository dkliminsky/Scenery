#ifndef CONTROLBOOLWIDGET_H
#define CONTROLBOOLWIDGET_H

#include <QCheckBox>
#include "nodes/controls/controlbool.h"

class ControlBoolWidget : public QCheckBox
{
    Q_OBJECT
public:
    explicit ControlBoolWidget(ControlBool *control, QWidget *parent = 0);
    
private:
    ControlBool *control;

signals:
    
public slots:
    void change();
    void update();
    
};

#endif // CONTROLBOOLWIDGET_H