#include "controlgroup.h"
#include <QJsonObject>
#include <QJsonArray>

ControlGroup::ControlGroup(QString name) :
    Control(Control::ControlGroup, name)
{

}

QJsonObject ControlGroup::getJson()
{
    QJsonObject controlObject;
    controlObject["name"] = name();

    QJsonArray controlsArray;
    QHashIterator<QString, Control *> i(_controls);
    while (i.hasNext()) {
        i.next();
        Control *control = i.value();
        controlsArray.append(control->getJson());
    }
    controlObject["controls"] = controlsArray;

    return controlObject;
}

void ControlGroup::setJson(QJsonObject json)
{
    QJsonArray controlsArray = json["controls"].toArray();
    for(int i=0; i<controlsArray.size(); i++) {
        QJsonObject controlObjectInner = controlsArray[i].toObject();
        QString name = controlObjectInner["name"].toString();
        if (_controls.contains(name)) {
            _controls[name]->setJson(controlObjectInner);
        }
    }
}
