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
	if (m_frameHelper.IsInitialized())
	{
		if (SUCCEEDED(m_frameHelper.UpdateColorFrame()))
		{
			Mat &colorMat = out.at(0)->mat;
			HRESULT hr = m_frameHelper.GetColorImage(&colorMat);
			if (FAILED(hr))	{
				return;
			}

			//imshow("Kinect color", m_colorMat);
		}
		else {
			//qDebug() << "Kinect: error update color frame";
		}

		if (SUCCEEDED(m_frameHelper.UpdateDepthFrame()))
		{
			Mat &depthMat = out.at(1)->mat;
			HRESULT hr = m_frameHelper.GetDepthImageAsArgb(&depthMat);
			if (FAILED(hr)) {
				return;
			}

			//imshow("Kinect depth", m_depthMat);
		}
	}
}

void KinectNode::openKinect(int)
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

				Mat &colorMat = out.at(0)->mat;
				DWORD width, height;
				m_frameHelper.GetColorFrameSize(&width, &height);
				colorMat.create(Size(width, height), m_frameHelper.COLOR_TYPE);

				Mat &depthMat = out.at(1)->mat;
				m_frameHelper.GetDepthFrameSize(&width, &height);
				depthMat.create(Size(width, height), m_frameHelper.DEPTH_RGB_TYPE);

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
