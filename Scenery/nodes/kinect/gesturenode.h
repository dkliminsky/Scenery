#ifndef GESTURENODE_H
#define GESTURENODE_H

#include "nodes/node.h"
#include "nodes/graphics/tools.h"


class GestureNode : public Node, Tools
{
public:
    GestureNode();
    virtual const QString name() { return "Gesture"; }
    virtual const QString tooltip() { return "Gesture"; }

protected:
    void run();

private:
    int inclination_deg;
    int time_interval;

    QTime time;
    int timer;
    int gest_time;
    bool gest_start;
};

#endif // GESTURENODE_H
