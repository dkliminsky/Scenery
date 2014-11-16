#ifndef ICONTROL_H
#define ICONTROL_H

#include <QString>

class IControl;
typedef QVector<IControl *> Controls;

class IControl
{
public:
    enum Type {
        ControlBool,
        ControlInt,
        ControlDouble,
        ControlString,
        ControlImage,
        ControlColor,
        ControlButton
    };

    IControl(Type type, QString name) { _type = type; _name = name; }
    virtual ~IControl() {}

    Type type() { return _type; }
    QString &name() { return _name; }
    virtual void set(QString &) {}
    virtual QString get() { return ""; }

protected:
    Type _type;
    QString _name;

};

#endif // ICONTROL_H
