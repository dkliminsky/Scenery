#ifndef DRAWING_H
#define DRAWING_H

#include "graphics/scene.h"

class Drawing : public Scene
{
public:
    Drawing();

    QString name() { return "Drawing"; }

    void setup();
    void paint();

private:
    Image *lineImage;

};

#endif // DRAWING_H
