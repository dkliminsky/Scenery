#ifndef DILATENODE_H
#define DILATENODE_H

#include <opencv2/opencv.hpp>
#include "nodes/node.h"


class DilateNode : public ThreadNode
{
public:
    DilateNode();
    virtual const QString name() { return "Dilate"; }
    virtual const QString tooltip() { return "Dilate"; }

protected:
    void run();

private:
    int dilation_size;
};

#endif // DILATENODE_H
