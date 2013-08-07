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

    IControl(Type type, QString name) { _type = type; _name = name; }

    Type type() { return _type; }
    QString &name() { return _name; }
    virtual void set(QString &data) = 0;
    virtual QString get() = 0;

protected:
    Type _type;
    QString _name;

};

#endif // ICONTROL_H
