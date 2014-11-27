#include "staticimage.h"

StaticImage::StaticImage()
{
    control(&imageStatic, "Image", "images/DK/", "white.png");
    control(backColor=Color(0,0,0,1), "Background");
}

void StaticImage::setup()
{
    background(0, 0, 0);
}

void StaticImage::paint()
{
    int w = width();
    int h = height();

    size(width(), height());
    color(backColor);
    //image(imageStatic, w/2, h/2, w, h-200);
    image(imageStatic, w/2, h/2, w, h);
}
