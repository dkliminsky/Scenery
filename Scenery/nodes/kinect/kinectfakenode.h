#ifndef KINECTFAKENODE_H
#define KINECTFAKENODE_H

#include "nodes/node.h"


class KinectNode : public Node
{
public:
    KinectNode(int device = 0);

    virtual const QString name() { return "Kinect"; }
    virtual const QString tooltip() { return "Kinect capture fake"; }

    static const int COLOR_TYPE = CV_8UC4;
    static const int DEPTH_TYPE = CV_16U;
    static const int DEPTH_RGB_TYPE = CV_8UC4;
};

#endif // KINECTFAKENODE_H
