#ifndef MANAGER2CAMERAS_H
#define MANAGER2CAMERAS_H

#include "manager.h"
#include "process/processdebug.h"
#include "server/server.h"

class Manager2Cameras : public Manager
{
public:
    Manager2Cameras();
    virtual QString name() { return "2 Cameras"; }

protected:\
    void timerEvent(QTimerEvent *);

private:
    ProcessDebug *debug0;
    ProcessDebug *debug1;
    Server *server;
};

#endif // MANAGER2CAMERAS_H
