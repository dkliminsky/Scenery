#ifndef HUMAN
#define HUMAN

#include <opencv2/opencv.hpp>
using namespace cv;

struct Human {
    int id;
    bool isTracking;
    Point hipCenter;
    Point spine;
    Point shoulderCenter;
    Point head;
    Point shoulderLeft;
    Point elbowLeft;
    Point wristLeft;
    Point handLeft;
    Point shoulderRight;
    Point elbowRight;
    Point wristRight;
    Point handRight;
    Point hipLeft;
    Point kneeLeft;
    Point ankleLeft;
    Point footLeft;
    Point hipRight;
    Point kneeRight;
    Point ankleRight;
    Point footRight;
};

#endif // HUMAN

