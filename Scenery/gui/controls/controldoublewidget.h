#ifndef CONTROLDOUBLEWIDGET_H
#define CONTROLDOUBLEWIDGET_H

#include <QDoubleSpinBox>
#include "controls/controldouble.h"

class ControlDoubleWidget : public QDoubleSpinBox
{
    Q_OBJECT
public:
    explicit ControlDoubleWidget(ControlDouble *control,
                                 QWidget *parent = 0);
    
private:
    ControlDouble *control;

signals:
    
public slots:
    void change();
    void update();

};

#endif // CONTROLDOUBLEWIDGET_H
