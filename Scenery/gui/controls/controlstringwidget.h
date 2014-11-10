#ifndef CONTROLSTRINGWIDGET_H
#define CONTROLSTRINGWIDGET_H

#include <QComboBox>
#include <QStringList>
#include "icontrolwidget.h"
#include "graphics/controls/controlstring.h"

class ControlStringWidget : public IControlWidget
{
    Q_OBJECT
public:
    explicit ControlStringWidget(ControlString *control);
    void update();

private:
    ControlString *control;
    QComboBox *comboBox;

signals:
    
private slots:
    void slotChange();

};

#endif // CONTROLSTRINGWIDGET_H
