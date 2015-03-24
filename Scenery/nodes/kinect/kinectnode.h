#ifndef KINECTNODE_H
#define KINECTNODE_H

#include <opencv2/opencv.hpp>
#define NOMINMAX
#include <Windows.h>
#include <NuiApi.h>
#include "nodes/node.h"
#include "nodes/kinect/OpenCVFrameHelper.h"
#include "nodes/kinect/OpenCVHelper.h"
#include "human.h"
using namespace cv;


class KinectNode : public ThreadNode
{
public:
	KinectNode(int device = 0);
	virtual const QString name() { return "Kinect"; }
	virtual const QString tooltip() { return "Kinect capture"; }

protected:
	void run();

private:
	Microsoft::KinectBridge::OpenCVFrameHelper m_frameHelper;
    OpenCVHelper m_openCVHelper;

	int device;
    NUI_IMAGE_RESOLUTION m_colorResolution;
    NUI_IMAGE_RESOLUTION m_depthResolution;

    bool isDrawDepthSkeleton;
    bool isDrawColorSkeleton;

	void openKinect(int device);
};

#endif // KINECTNODE_H
