#include "particle.h"
#include <QDebug>

Particle::Particle(Image *image, bool copy)
{
    isCopy = copy;
    if (copy) {
        _image = new Image(image);
    }
    else {
        _image = image;
    }

    _accX = 0;
    _accY = 0;
    _accX2 = 0;
    _accY2 = 0;
    _decX = 1;
    _decY = 1;
    _decX2 = 1;
    _decY2 = 1;
}

Particle::~Particle()
{
    if (isCopy)
        delete _image;
}

void Particle::setPos(float x, float y, float w, float h)
{
    _x = x; _y = y; w = _w; _h = h;
}

void Particle::setPos(Rect pos)
{
    _x = pos.x; _y = pos.y; _w = pos.width; _h = pos.height;
}

void Particle::setAcceleration(float x, float y, float x2, float y2)
{
    _accX = x;
    _accY = y;
    _accX2 = x2;
    _accY2 = y2;
}

void Particle::setDeceleration(float x, float y, float x2, float y2)
{
    _decX = x;
    _decY = y;
    _decX2 = x2;
    _decY2 = y2;
}

void Particle::process(int dtime)
{
    _ttl -= dtime;
    _x += _accX * float(dtime);
    _y += _accY * float(dtime);
}

