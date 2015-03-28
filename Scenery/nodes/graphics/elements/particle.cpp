#include "particle.h"

Particle::Particle(Image *image, bool copy)
{
    isCopy = copy;
    if (copy) {

    }
    else {
        _image = image;
    }
}

Particle::~Particle()
{

}

void Particle::setPos(float x, float y, float w, float h)
{
    _x = x; _y = y; w = _w; _h = h;
}

void Particle::setPos(Rect pos)
{
    _x = pos.x; _y = pos.y; _w = pos.width; _h = pos.height;
}

