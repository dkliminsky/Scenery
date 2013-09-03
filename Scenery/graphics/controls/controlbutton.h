#ifndef CONTROLBUTTON_H
#define CONTROLBUTTON_H

#include <QVector>
#include "icontrol.h"

class ControlButton : public IControl
{
public:
    struct Button {
        int id;
        QString name;
    };

    ControlButton(QString name, QVector<Button> buttons);
    QVector<Button> getButtons() { return buttons; }

private:
    QVector<Button> buttons;
};

#endif // CONTROLBUTTON_H
