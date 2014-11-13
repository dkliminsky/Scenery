#ifndef DEBUGNODE_H
#define DEBUGNODE_H

#include <opencv2/opencv.hpp>
#include "process/node.h"

using namespace cv;


class DebugNode : public ThreadNode
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
