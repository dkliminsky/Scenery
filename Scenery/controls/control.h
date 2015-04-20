#ifndef CONTROL_H
#define CONTROL_H

#include <QString>

class Control;
typedef QVector<Control *> Controls;

class Control
{
public:
    enum Type {
        ControlBool,
        ControlInt,
        ControlDouble,
        ControlString,
        ControlImage,
        ControlColor,
        ControlButton,
        ControlGroup
    };

    Control(Type type, QString name) { _type = type; _name = name; }
    virtual ~Control() {}

    Type type() { return _type; }
    QString &name() { return _name; }
    virtual void set(QString &) {}
    virtual QString get() { return ""; }

protected:
    Type _type;
    QString _name;

};

#endif // CONTROL_H
