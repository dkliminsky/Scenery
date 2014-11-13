#ifndef COLORNODE_H
#define COLORNODE_H

#include <opencv2/opencv.hpp>
#include "process/node.h"
using namespace cv;


class ColorNode : public ThreadNode
{
public:
    ColorNode();
    virtual const QString name() { return "Color"; }
    virtual const QString tooltip() { return "Convert color"; }

protected:
    void run();

};

#endif // COLORNODE_H
