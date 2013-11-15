#ifndef STARS_H
#define STARS_H

#include "graphics/scene.h"

class Stars : public Scene
{
public:
    Stars();
    QString name() { return "Stars"; }

    void setup();
    void paint();

private:
    double inkingLengthLimit;
    double starProb;
    int starTTL;
    double starSize;
    double starSpeed;
    double starAcceleration;

    Image *imageStar;

    struct Star {
        float x;
        float y;
        float speed;
        float size;

        int ttl;
    };
    QList<Star> stars;

    void createStar(float x, float y);

};

#endif // STARS_H
