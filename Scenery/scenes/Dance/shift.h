#ifndef SHIFT_H
#define SHIFT_H

#include "graphics/scene.h"

class Shift : public Scene
{
public:
    Shift();

    QString name() { return "Shift"; }

    void setup();
    void resize();
    void paint();

private:
    int width;
    int height;
    Image *imageShift;

};

#endif // SHIFT_H
