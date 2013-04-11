#ifndef BRUSH_H
#define BRUSH_H

#include "graphics/scene.h"

class Brush : public Scene
{
public:
    Brush();

    QString name() { return "Brush"; }

    void setup();
    void paint();

private:
    bool isBlot;
    Color blotColor;
    Image *blotImages[10];
    int blotSize;
    int blotLimit;
};

#endif // BRUSH_H
