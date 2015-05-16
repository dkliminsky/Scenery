#include "kinectnode.h"


KinectNode::KinectNode(int device) :
	device(device)
{
	METHOD_BEGIN

    addControl(isDrawDepthSkeleton=true, "Depth skeleton");
    addControl(isDrawColorSkeleton=true, "Color skeleton");
    addControl(isHReverse=false, "Horisontal reverse");

	outputs.append(new Port(PortType::Mat));
	outputs.append(new Port(PortType::Mat));
    outputs.append(new Port(PortType::Human));

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
    Human &human = outputs.at(2)->human;

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

        human.isTracking = false;
        for (int i=0; i < NUI_SKELETON_COUNT; ++i) {

            NUI_SKELETON_TRACKING_STATE trackingState =
                    skeletonFrame.SkeletonData[i].eTrackingState;

            if (trackingState == NUI_SKELETON_TRACKED ||
                trackingState == NUI_SKELETON_POSITION_INFERRED) {

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
                human.hipCenter = jointPositions[NUI_SKELETON_POSITION_HIP_CENTER];
                human.spine = jointPositions[NUI_SKELETON_POSITION_SPINE];
                human.shoulderCenter = jointPositions[NUI_SKELETON_POSITION_SHOULDER_CENTER];
                human.head = jointPositions[NUI_SKELETON_POSITION_HEAD];
                human.shoulderLeft = jointPositions[NUI_SKELETON_POSITION_SHOULDER_LEFT];
                human.elbowLeft = jointPositions[NUI_SKELETON_POSITION_ELBOW_LEFT];
                human.wristLeft = jointPositions[NUI_SKELETON_POSITION_WRIST_LEFT];
                human.handLeft = jointPositions[NUI_SKELETON_POSITION_HAND_LEFT];
                human.shoulderRight = jointPositions[NUI_SKELETON_POSITION_SHOULDER_RIGHT];
                human.elbowRight = jointPositions[NUI_SKELETON_POSITION_ELBOW_RIGHT];
                human.wristRight = jointPositions[NUI_SKELETON_POSITION_WRIST_RIGHT];
                human.handRight = jointPositions[NUI_SKELETON_POSITION_HAND_RIGHT];
                human.hipLeft = jointPositions[NUI_SKELETON_POSITION_HIP_LEFT];
                human.kneeLeft = jointPositions[NUI_SKELETON_POSITION_KNEE_LEFT];
                human.ankleLeft = jointPositions[NUI_SKELETON_POSITION_ANKLE_LEFT];
                human.footLeft = jointPositions[NUI_SKELETON_POSITION_FOOT_LEFT];
                human.hipRight = jointPositions[NUI_SKELETON_POSITION_HIP_RIGHT];
                human.kneeRight = jointPositions[NUI_SKELETON_POSITION_KNEE_RIGHT];
                human.ankleRight = jointPositions[NUI_SKELETON_POSITION_ANKLE_RIGHT];
                human.footRight = jointPositions[NUI_SKELETON_POSITION_FOOT_RIGHT];
                break;
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
