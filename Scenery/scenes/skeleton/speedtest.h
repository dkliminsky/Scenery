#ifndef SPEEDTEST_H
#define SPEEDTEST_H

#include "graphics/scene.h"

class SpeedTest : public Scene
{
public:
    SpeedTest();

    QString name() { return "SpeedTest"; }

    void paint();

private:
    Image *imageSprite;
    Image *images[4];

    int sizeImage;
    int count;
};

#endif // SPEEDTEST_H
