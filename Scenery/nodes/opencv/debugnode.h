#ifndef DEBUGNODE_H
#define DEBUGNODE_H

#include <opencv2/opencv.hpp>
#include "nodes/node.h"

using namespace cv;


class DebugNode : public Node
{
public:
    DebugNode();

    virtual const QString name() { return "Debug"; }
    virtual const QString tooltip() { return "Debug view image"; }

protected:
    void run();

private:
    int num;

};

#endif // DEBUGNODE_H
