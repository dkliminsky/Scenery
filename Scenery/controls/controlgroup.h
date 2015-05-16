#ifndef CONTROLGROUP_H
#define CONTROLGROUP_H

#include "control.h"

class ControlGroup : public Control
{
public:
    explicit ControlGroup(QString name);

    virtual QJsonObject getJson();
    virtual void setJson(QJsonObject json);

};

#endif // CONTROLGROUP_H
