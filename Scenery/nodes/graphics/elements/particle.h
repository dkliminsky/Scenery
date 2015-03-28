#ifndef PARTICLE_H
#define PARTICLE_H

#include "nodes/graphics/elements/image.h"
#include <opencv2/opencv.hpp>
using namespace cv;

class Particle
{
public:
    Particle(Image *image, bool copy=true);
    ~Particle();

    Image *image() { return _image; }
    float x() { return _x; }
    float y() { return _y; }
    float w() { return _w; }
    float h() { return _h; }

    void setPos(float x, float y, float w, float h);
    void setPos(Rect pos);

    int ttl() { return _ttl; }
    void setTTL(int ttl) { _ttl = ttl; }

private:
    Image *_image;
    bool isCopy;
    int _ttl;
    float _x, _y, _w, _h;
};

#endif // PARTICLE_H
