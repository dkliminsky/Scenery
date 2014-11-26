#ifndef SHADOWSCENE_H
#define SHADOWSCENE_H

#include <opencv2/opencv.hpp>
#include "nodes/graphics/scene.h"
using namespace cv;


class ShadowScene : public Scene
{
public:
    ShadowScene();

    QString name() { return "Welcome"; }

    void setup();
    void resize();
    void paint();

private:
    Image imageShadow;
    int shadow_width;
    int shadow_height;
    int shadow_vertical;
    int shadow_shift;
    Color backColor;
    Color shadowColor;

    int depth_min;
    int depth_max;

    bool is_active;
    bool is_reverse;

};

#endif // SHADOWSCENE_H
