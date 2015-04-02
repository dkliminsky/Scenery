#ifndef RECTNODE_H
#define RECTNODE_H

#include "nodes/node.h"

class RectNode : public Node
{
public:
    RectNode();
    virtual const QString name() { return "Rect"; }
    virtual const QString tooltip() { return "Rect"; }

protected:
    void run();

private:
    int x;
    int y;
    int w;
    int h;
};
#endif // RECTNODE_H
