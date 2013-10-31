#ifndef MANAGERDK_H
#define MANAGERDK_H

#include "manager.h"
#include "process/processdebug.h"

#include "scenes/skeleton/skeleton.h"
#include "scenes/skeleton/speedtest.h"
#include "scenes/DK/staticimage.h"
#include "scenes/DK/effect01.h"
#include "scenes/DK/effect02.h"
#include "scenes/DK/effect03.h"

class ManagerDK : public Manager
{
public:
    ManagerDK();
    ~ManagerDK();

    virtual QString name() { return "DK"; }

protected:
    void timerEvent(QTimerEvent *);

private:
    ProcessDebug *debug;

};

#endif // MANAGERDK_H
