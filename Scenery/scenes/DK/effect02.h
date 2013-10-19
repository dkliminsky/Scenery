#ifndef EFFECT02_H
#define EFFECT02_H

#include "graphics/scene.h"

class Effect02 : public Scene
{
public:
    Effect02();

    QString name() { return "Effect 01 Circles"; }

    void setup();
    void paint();

private:
    Image *imageCircle;
    Image *imageCircle2;

    Color backColor;
    Color circleColor[7];
    int circleDeviation;
    int circleTimeLife;
    int circleTimeDisappear;
    double circleAlphaDisappear;
    int circleTimeGrow;
    int circleGrowSize;


    struct Circle {
        float x;
        float y;
        float angle;
        float size;
        int ttl;
        int grow;
        Color color;
    };
    QList<Circle> circles;

};

#endif // EFFECT02_H
