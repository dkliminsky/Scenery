#ifndef MANAGERVLMT_H
#define MANAGERVLMT_H

#include "manager.h"

#include "scenes/skeleton.h"
#include "scenes/VLMT/cage.h"
#include "scenes/VLMT/strings.h"
#include "scenes/VLMT/brush.h"
#include "scenes/VLMT/inking.h"

#include "gui/processdebug.h"

class ManagerVLMT : public Manager
{
public:
    ManagerVLMT();
    ~ManagerVLMT();

private:
    void timerEvent(QTimerEvent *);

private:
    ProcessDebug *debug;

};

#endif // MANAGERVLMT_H
