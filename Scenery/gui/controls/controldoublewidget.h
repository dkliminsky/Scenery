#ifndef CONTROLDOUBLEWIDGET_H
#define CONTROLDOUBLEWIDGET_H

#include <QDoubleSpinBox>
#include "icontrolwidget.h"
#include "graphics/controls/controldouble.h"

class ControlDoubleWidget : public IControlWidget
{
    Q_OBJECT
public:
    explicit ControlDoubleWidget(ControlDouble *control);
    void update();
    
private:
    ControlDouble *control;
    QDoubleSpinBox *doubleSpinBox;

signals:
    
private slots:
    void slotChange();

};

#endif // CONTROLDOUBLEWIDGET_H
