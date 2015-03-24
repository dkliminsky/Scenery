#include "kinectnode.h"


KinectNode::KinectNode(int device) :
	device(device)
{
	METHOD_BEGIN

    control(isDrawDepthSkeleton=true, "Depth skeleton");
    control(isDrawColorSkeleton=true, "Color skeleton");

	outputs.append(new Port(PortType::Mat));
	outputs.append(new Port(PortType::Mat));
    outputs.append(new Port(PortType::Humans));

    for (int i=0; i < NUI_SKELETON_COUNT; i++) {
        Human human;
        outputs.at(2)->humans.push_back(human);
    }

    m_colorResolution = NUI_IMAGE_RESOLUTION_640x480;
    m_depthResolution = NUI_IMAGE_RESOLUTION_320x240;
    m_frameHelper.SetColorFrameResolution(m_colorResolution);
    m_frameHelper.SetDepthFrameResolution(m_depthResolution);

	openKinect(device);

	METHOD_END
}

void KinectNode::run()
{
    Mat &colorMat = outputs.at(0)->mat;
    Mat &depthMat = outputs.at(1)->mat;

    if (!m_frameHelper.IsInitialized()) {
        return;
    }


    if (SUCCEEDED(m_frameHelper.UpdateColorFrame())) {
        HRESULT hr = m_frameHelper.GetColorImage(&colorMat);
        if (FAILED(hr))	{
            return;
        }
    }

    if (SUCCEEDED(m_frameHelper.UpdateDepthFrame())) {
        HRESULT hr = m_frameHelper.GetDepthImageAsArgb(&depthMat);
        if (FAILED(hr)) {
            return;
        }
    }

    if (SUCCEEDED(m_frameHelper.UpdateSkeletonFrame())) {
        vector<Human> &humans = outputs.at(2)->humans;
        for (int i=0; i < NUI_SKELETON_COUNT; i++) {
            humans.at(i).isTracking = false;
        }

        NUI_SKELETON_FRAME skeletonFrame;
        HRESULT hr = m_frameHelper.GetSkeletonFrame(&skeletonFrame);
        if (FAILED(hr)) {
            return;
        }

        if (isDrawColorSkeleton) {
            hr = m_openCVHelper.DrawSkeletonsInColorImage(&colorMat,
                                                          &skeletonFrame,
                                                          m_colorResolution,
                                                          m_depthResolution);

            if (FAILED(hr)) {
                qDebug() << "Sceleton fail";
            }
        }

        if (isDrawDepthSkeleton) {
            hr = m_openCVHelper.DrawSkeletonsInDepthImage(&depthMat,
                                                          &skeletonFrame,
                                                          m_depthResolution);
            if (FAILED(hr)) {
                qDebug() << "Sceleton fail";
            }
        }

        for (int i=0; i < NUI_SKELETON_COUNT; ++i) {

            NUI_SKELETON_TRACKING_STATE trackingState =
                    skeletonFrame.SkeletonData[i].eTrackingState;

            Human &human = humans.at(i);
            if (trackingState == NUI_SKELETON_TRACKED) {
                // Draw entire skeleton
                NUI_SKELETON_DATA *pSkel = &(skeletonFrame.SkeletonData[i]);
                Point jointPositions[NUI_SKELETON_POSITION_COUNT];
                for (int j = 0; j < NUI_SKELETON_POSITION_COUNT; ++j) {
                    LONG x, y;
                    m_openCVHelper.GetCoordinatesForSkeletonPoint(
                                pSkel->SkeletonPositions[j], &x, &y,
                                m_colorResolution, m_depthResolution);
                    jointPositions[j] = Point(x, y);
                }

                human.isTracking = true;
                human.head = jointPositions[NUI_SKELETON_POSITION_HEAD];
                human.wristRight = jointPositions[NUI_SKELETON_POSITION_WRIST_RIGHT];
                human.wristLeft = jointPositions[NUI_SKELETON_POSITION_WRIST_LEFT];
                human.footRight = jointPositions[NUI_SKELETON_POSITION_FOOT_RIGHT];
                human.footLeft = jointPositions[NUI_SKELETON_POSITION_FOOT_LEFT];

            }
            else if (trackingState == NUI_SKELETON_POSITION_INFERRED) {
                // Draw a filled circle at the skeleton's inferred position
//                    LONG x, y;
//                    GetCoordinatesForSkeletonPoint(pSkeletons->SkeletonData[i].Position, &x, &y, colorResolution, depthResolution);
//                    circle(*pImg, Point(x, y), 7, SKELETON_COLORS[i], CV_FILLED);
            }
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

				Mat &colorMat = outputs.at(0)->mat;
				DWORD width, height;
				m_frameHelper.GetColorFrameSize(&width, &height);
				colorMat.create(Size(width, height), m_frameHelper.COLOR_TYPE);

				Mat &depthMat = outputs.at(1)->mat;
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
