#ifndef CONTROLCOLOR_H
#define CONTROLCOLOR_H

#include "icontrol.h"
#include "../elements/color.h"

class ControlColor : public IControl
{
public:
    ControlColor(Color &color, QString name);
    void set(QString &color);
    QString get();

    Color &value() { return _color; }

private:
    Color &_color;

};

#endif // CONTROLCOLOR_H
