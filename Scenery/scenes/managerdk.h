#ifndef MANAGERDK_H
#define MANAGERDK_H

#include "manager.h"
#include "process/processdebug.h"

#include "scenes/Skeleton/skeleton.h"
#include "scenes/VLMT/cage.h"
#include "scenes/VLMT/strings.h"
#include "scenes/VLMT/brush.h"
#include "scenes/VLMT/inking.h"
#include "scenes/DK/effect01.h"

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
