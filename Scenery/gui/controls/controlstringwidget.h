#ifndef CONTROLSTRINGWIDGET_H
#define CONTROLSTRINGWIDGET_H

#include <QComboBox>
#include <QStringList>
#include "graphics/controls/controlstring.h"

class ControlStringWidget : public QComboBox
{
    Q_OBJECT
public:
    explicit ControlStringWidget(ControlString *control,
                                 QWidget *parent = 0);

private:
    ControlString *control;

signals:
    
public slots:
    void change();
    void update();

};

#endif // CONTROLSTRINGWIDGET_H
