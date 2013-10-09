#ifndef MANAGERDANCE_H
#define MANAGERDANCE_H

#include "manager.h"

#include "scenes/Skeleton/skeleton.h"
#include "scenes/Dance/shift.h"
#include "scenes/Dance/danceeffects.h"
#include "scenes/Dance/memorize.h"
#include "scenes/Dance/dancestrings.h"

#include "process/processdebug.h"

class ManagerDance : public Manager
{
public:
    ManagerDance();
    virtual QString name() { return "Dances"; }

protected:
    void timerEvent(QTimerEvent *);

private:
    ProcessDebug *debug;

};

#endif // MANAGERDANCE_H
