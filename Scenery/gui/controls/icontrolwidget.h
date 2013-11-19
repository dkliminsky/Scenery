#ifndef ICONTROLWIDGET_H
#define ICONTROLWIDGET_H

#include <QWidget>

class IControlWidget : public QWidget
{
    Q_OBJECT
public:
    virtual void update(){}

};

#endif // ICONTROLWIDGET_H
