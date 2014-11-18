#ifndef KINECTNODE_H
#define KINECTNODE_H

#include <opencv2/opencv.hpp>
#define NOMINMAX
#include <Windows.h>
#include <NuiApi.h>
#include "nodes/node.h"
#include "nodes/kinect/OpenCVFrameHelper.h"
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

	int device;
	Mat m_colorMat;
	Mat m_depthMat;

	void openKinect(int device);
};

#endif // KINECTNODE_H
