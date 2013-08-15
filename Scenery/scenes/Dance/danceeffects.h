#ifndef DANCEEFFECTS_H
#define DANCEEFFECTS_H

#include "graphics/scene.h"

class DanceEffects : public Scene
{
public:
    DanceEffects();

    QString name() { return "Dance Effects"; }

    void setup();
    void resize();
    void paint();

private:
    Image *imageFlare;

};

#endif // DANCEEFFECTS_H
