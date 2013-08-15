#ifndef MANAGERTV_H
#define MANAGERTV_H

#include "manager.h"
#include "process/processdebug.h"

class ManagerTV : public Manager
{
public:
    ManagerTV();
    ~ManagerTV();

    virtual QString name() { return "Face"; }

protected:
    void timerEvent(QTimerEvent *);

private:
    ProcessDebug *debug;


};

#endif // MANAGERTV_H
