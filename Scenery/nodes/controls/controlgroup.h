#ifndef CONTROLGROUP_H
#define CONTROLGROUP_H

#include "icontrol.h"

class ControlGroup : public IControl
{
public:
    ControlGroup(QString name);
    ~ControlGroup();
};

#endif // CONTROLGROUP_H
