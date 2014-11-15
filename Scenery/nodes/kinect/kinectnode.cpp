#include "kinectnode.h"


KinectNode::KinectNode(int device) :
	device(device)
{
	METHOD_BEGIN

	out.append(new Port(PortType::Mat));
	out.append(new Port(PortType::Mat));
	openKinect(device);

	METHOD_END
}

void KinectNode::run()
{

}

void KinectNode::openKinect(int device)
{
	qDebug() << "Kinect: initializating...";

	// If Kinect is already initialized, return
	if (m_frameHelper.IsInitialized())
	{
		qDebug() << "Kinect: already init";
		return;
	}

	HRESULT hr;

	// Get number of Kinect sensors
	int sensorCount = 0;
	hr = NuiGetSensorCount(&sensorCount);
	if (FAILED(hr))
	{
		qDebug() << "Kinect: failed get sensor count";
		return;
	}

	// If no sensors, update status bar to report failure and return
	if (sensorCount == 0)
	{
		qDebug() << "Kinect: sensor not found";
		return;
	}

	// Iterate through Kinect sensors until one is successfully initialized
	for (int i = 0; i < sensorCount; ++i)
	{
		INuiSensor* sensor = NULL;
		hr = NuiCreateSensorByIndex(i, &sensor);
		if (SUCCEEDED(hr))
		{
			hr = m_frameHelper.Initialize(sensor);
			if (SUCCEEDED(hr))
			{
				qDebug() << "Kinect: success connected";
				return;
			}
			else
			{
				qDebug() << "Kinect: not ready";
				m_frameHelper.UnInitialize();
			}
		}
	}

	qDebug() << "Kinect: failure init";
}