#ifndef CONTROL_H
#define CONTROL_H

#include <QString>
#include <QHash>
#include <QJsonObject>

class Control;
typedef QHash<QString, Control *> Controls;

class Control
{
public:
    enum Type {
        ControlGroup,
        ControlBool,
        ControlInt,
        ControlDouble,
        ControlString,
        ControlImage,
        ControlColor,
        ControlButton
    };

    Control(Type type, QString name);
    virtual ~Control() {}

    Type type() { return _type; }
    QString &name() { return _name; }
    void setName(QString name) { _name = name; }
    int number() { return _number; }
    void setNumber(int number) { _number = number; }
    void insertControl(Control *control);
    Controls &controls() { return _controls; }

    virtual void set(QString &) {}
    virtual QString get() { return ""; }

    virtual QJsonObject getJson();
    virtual void setJson(QJsonObject controlObject);

protected:
    Type _type;
    QString _name;

    Controls _controls;
    int _number;
    int cur_inner_number;

};

#endif // CONTROL_H
