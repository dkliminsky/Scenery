#ifndef ERODENODE_H
#define ERODENODE_H

#include <opencv2/opencv.hpp>
#include "nodes/node.h"


class ErodeNode : public ThreadNode
{
public:
    ErodeNode();
    virtual const QString name() { return "Erode"; }
    virtual const QString tooltip() { return "Erode"; }

protected:
    void run();

private:
    int erosion_size;

};

#endif // ERODENODE_H
