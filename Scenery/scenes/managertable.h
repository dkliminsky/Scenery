#ifndef MANAGERTABLE_H
#define MANAGERTABLE_H

#include "manager.h"
#include "process/processdebug.h"

#include "table/fractals.h"

class ManagerTable : public Manager
{
public:
    ManagerTable();

    virtual QString name() { return "Virtual Table"; }

protected:
    void timerEvent(QTimerEvent *);

private:
    ProcessDebug *debug;

};

#endif // MANAGERTABLE_H
