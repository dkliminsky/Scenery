#ifndef MANAGERMOTION_H
#define MANAGERMOTION_H

#include "manager.h"
#include "process/processdebug.h"
#include "server/server.h"

class ManagerMotion : public Manager
{
public:
    ManagerMotion();
    virtual QString name() { return "Motion"; }

protected:
    void timerEvent(QTimerEvent *);

private:
    ProcessDebug *debug;
    Server *server;
};

#endif // MANAGERMOTION_H
