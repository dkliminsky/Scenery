#include "fractals.h"

Fractals::Fractals()
{
}

void Fractals::setup()
{

}

void Fractals::resize()
{
    background(0, 0, 0, 1);
}

void Fractals::paint()
{
    int width = process(0)->width();
    int height = process(0)->height();

    size(width, height);
    background(0, 0, 0, 0.1);

    color(1, 0, 0);
    line(random(200), random(200), random(200), random(200));
}

