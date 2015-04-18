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


};

#endif // GESTURENODE_H
