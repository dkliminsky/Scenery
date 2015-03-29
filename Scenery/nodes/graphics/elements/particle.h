#ifndef PARTICLE_H
#define PARTICLE_H

#include "nodes/graphics/elements/elements.h"
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

    Color color() { return _color; }
    void setColor(Color color) { _color = color; }

    int ttl() { return _ttl; }
    void setTTL(int ttl) { _ttl = ttl; }

    void setAcceleration(float x, float y, float x2=0, float y2=0);
    void setDeceleration(float x, float y, float x2=1, float y2=1);

    virtual void process(int dtime);

private:
    Image *_image;
    Color _color;
    bool isCopy;
    int _ttl;
    float _x, _y, _w, _h;
    float _accX, _accY, _accX2, _accY2;
    float _decX, _decY, _decX2, _decY2;
};

#endif // PARTICLE_H
