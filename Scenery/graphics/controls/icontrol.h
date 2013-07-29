#ifndef ICONTROL_H
#define ICONTROL_H

#include <QString>

class IControl
{
public:
    enum Type {
        ControlBool,
        ControlInt,
        ControlDouble,
        ControlString,
        ControlImage,
        ControlColor
    };

    IControl(QString name) { _name = name; }

    QString &name() { return _name; }
    virtual void set(QString &data) = 0;
    virtual QString get() = 0;

protected:
    QString _name;

};

#endif // ICONTROL_H
