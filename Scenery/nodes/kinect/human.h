#ifndef HUMAN
#define HUMAN

#include <opencv2/opencv.hpp>
using namespace cv;

class Human
{
public:
    int id;
    bool isTracking;
    Point2f hipCenter;
    Point2f spine;
    Point2f shoulderCenter;
    Point2f head;
    Point2f shoulderLeft;
    Point2f elbowLeft;
    Point2f wristLeft;
    Point2f handLeft;
    Point2f shoulderRight;
    Point2f elbowRight;
    Point2f wristRight;
    Point2f handRight;
    Point2f hipLeft;
    Point2f kneeLeft;
    Point2f ankleLeft;
    Point2f footLeft;
    Point2f hipRight;
    Point2f kneeRight;
    Point2f ankleRight;
    Point2f footRight;

    void translate(Rect pos) {
        float kx = float(pos.width)/float(640);
        float ky = float(pos.height)/float(480);
        float dx = pos.x - pos.width/2;
        float dy = pos.y - pos.height/2;

        hipCenter.x = hipCenter.x*kx + dx;
        hipCenter.y = hipCenter.y*ky + dy;
        spine.x = spine.x*kx + dx;
        spine.y = spine.y*ky + dy;
        shoulderCenter.x = shoulderCenter.x*kx + dx;
        shoulderCenter.y = shoulderCenter.y*ky + dy;
        head.x = head.x*kx + dx;
        head.y = head.y*ky + dy;
        shoulderLeft.x = shoulderLeft.x*kx + dx;
        shoulderLeft.y = shoulderLeft.y*ky + dy;
        elbowLeft.x = elbowLeft.x*kx + dx;
        elbowLeft.y = elbowLeft.y*ky + dy;
        wristLeft.x = wristLeft.x*kx + dx;
        wristLeft.y = wristLeft.y*ky + dy;
        handLeft.x = handLeft.x*kx + dx;
        handLeft.y = handLeft.y*ky + dy;
        shoulderRight.x = shoulderRight.x*kx + dx;
        shoulderRight.y = shoulderRight.y*ky + dy;
        elbowRight.x = elbowRight.x*kx + dx;
        elbowRight.y = elbowRight.y*ky + dy;
        wristRight.x = wristRight.x*kx + dx;
        wristRight.y = wristRight.y*ky + dy;
        handRight.x = handRight.x*kx + dx;
        handRight.y = handRight.y*ky + dy;
        hipLeft.x = hipLeft.x*kx + dx;
        hipLeft.y = hipLeft.y*ky + dy;
        kneeLeft.x = kneeLeft.x*kx + dx;
        kneeLeft.y = kneeLeft.y*ky + dy;
        ankleLeft.x = ankleLeft.x*kx + dx;
        ankleLeft.y = ankleLeft.y*ky + dy;
        footLeft.x = footLeft.x*kx + dx;
        footLeft.y = footLeft.y*ky + dy;
        hipRight.x = hipRight.x*kx + dx;
        hipRight.y = hipRight.y*ky + dy;
        kneeRight.x = kneeRight.x*kx + dx;
        kneeRight.y = kneeRight.y*ky + dy;
        ankleRight.x = ankleRight.x*kx + dx;
        ankleRight.y = ankleRight.y*ky + dy;
        footRight.x = footRight.x*kx + dx;
        footRight.y = footRight.y*ky + dy;
    }

};

#endif // HUMAN

