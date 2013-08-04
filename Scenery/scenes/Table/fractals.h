#ifndef FRACTALS_H
#define FRACTALS_H

#include "graphics/scene.h"

class Fractals : public Scene
{
public:
    Fractals();

    QString name() { return "Fractals"; }

    void setup();
    void resize();
    void paint();

};

#endif // FRACTALS_H
