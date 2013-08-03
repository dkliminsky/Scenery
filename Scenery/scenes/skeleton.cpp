#include "skeleton.h"
#include <QDebug>

Skeleton::Skeleton()
{
    imageShip = loadImage("ship_512.png");
}

void Skeleton::setup()
{

}

void Skeleton::resize()
{
    background(0, 0, 0, 1);
}

void Skeleton::paint()
{
    size(200, 200);
    background(0, 0, 0, 0.1);
    color(1, 0, 0);
    line(random(200), random(200), random(200), random(200));
    color(1, 1, 1, 1);
    image(imageShip, 100, 100, 90, 90);
    color(0, 0, 1, 1);
    text(random(width()), random(height()), "blablabla", QFont("Times", 10));

    color(1, 1, 1, 1);
    text(30, 30, QString().number(process(0)->width()),  QFont("Times", 10));
    text(60, 30, QString().number(process(0)->height()), QFont("Times", 10));
}

