#include "control.h"
#include "debug.h"
#include <QJsonObject>
#include <QJsonArray>

Control::Control(Control::Type type, QString name) :
    _type(type),
    _name(name),
    _number(0),
    cur_inner_number(0)
{

}

Control::~Control()
{
    METHOD_BEGIN

    QHashIterator<QString, Control *> i(_controls);
    while (i.hasNext()) {
        i.next();
        Control *control = i.value();
        qDebug() << "Delete Control:" << control->name();
        //delete control;
    }

    METHOD_END
}

void Control::insertControl(Control *control)
{
    control->setNumber(cur_inner_number);
    cur_inner_number++;
    _controls.insert(control->name(), control);
}

QJsonObject Control::getJson()
{
    QJsonObject controlObject;
    controlObject["name"] = name();

    if (_type == Control::ControlGroup) {
        QJsonArray controlsArray;
        QHashIterator<QString, Control *> i(_controls);
        while (i.hasNext()) {
            i.next();
            Control *control = i.value();
            controlsArray.append(control->getJson());
        }
        controlObject["controls"] = controlsArray;
    }
    else {
       controlObject["data"] = get();
    }
    return controlObject;
}

void Control::setJson(QJsonObject json)
{
    if (_type == Control::ControlGroup) {
        QJsonArray controlsArray = json["controls"].toArray();
        for(int i=0; i<controlsArray.size(); i++) {
            QJsonObject controlObjectInner = controlsArray[i].toObject();
            QString name = controlObjectInner["name"].toString();
            if (_controls.contains(name)) {
                _controls[name]->setJson(controlObjectInner);
            }
        }
    }
    else {
        set(json["data"].toString());
    }
}
