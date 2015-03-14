#ifndef PROCESS_H
#define PROCESS_H

#include "opencv/cameranode.h"
#include "opencv/debugnode.h"
#include "opencv/colornode.h"
#include "opencv/erodenode.h"
#include "opencv/dilatenode.h"

#include "graphics/scenesnode.h"
#include "graphics/view.h"

#ifdef NOKINECT
#include "kinect/kinectfakenode.h"
#else
#include "kinect/kinectnode.h"
#endif

#endif // PROCESS_H
