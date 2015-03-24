#ifndef HUMAN
#define HUMAN

#include <opencv2/opencv.hpp>
using namespace cv;

struct Human {
    int id;
    bool isTracking;
    Point head;
    Point wristRight;
    Point wristLeft;
    Point footRight;
    Point footLeft;
};

#endif // HUMAN

