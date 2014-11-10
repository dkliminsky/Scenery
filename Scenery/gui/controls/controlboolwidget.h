#ifndef CONTROLBOOLWIDGET_H
#define CONTROLBOOLWIDGET_H

#include <QCheckBox>
#include "icontrolwidget.h"
#include "graphics/controls/controlbool.h"

class ControlBoolWidget : public IControlWidget
{
    Q_OBJECT
public:
    explicit ControlBoolWidget(ControlBool *control);
    void update();

private:
    ControlBool *control;
    QCheckBox *checkBox;

signals:
    
private slots:
    void slotChange();
    
};

#endif // CONTROLBOOLWIDGET_H
