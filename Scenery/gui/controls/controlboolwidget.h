#ifndef CONTROLBOOLWIDGET_H
#define CONTROLBOOLWIDGET_H

#include <QCheckBox>
#include "graphics/controls/controlbool.h"

class ControlBoolWidget : public QCheckBox
{
    Q_OBJECT
public:
    explicit ControlBoolWidget(ControlBool *control, QWidget *parent = 0);
    
private:
    ControlBool *control;

signals:
    
public slots:
    void slotChange();
    
};

#endif // CONTROLBOOLWIDGET_H
