#ifndef CAMERAPOSITIONNODE_H
#define CAMERAPOSITIONNODE_H

#include "nodes/node.h"

class CameraPositionNode : public Node
{
public:
    CameraPositionNode();
    virtual const QString name() { return "Camera Position"; }
    virtual const QString tooltip() { return "Camera Position"; }

protected:
    void run();

private:
    int x;
    int y;
    int w;
    int h;
};

#endif // CAMERAPOSITIONNODE_H
