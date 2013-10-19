#include "staticimage.h"

StaticImage::StaticImage()
{
    qDebug() << "!!";
    control(&imageStatic, "Image", "images/DK/", "image.png");
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
    color(1,1,1,1);
    image(imageStatic, w/2, h/2, w, h-200);
}
