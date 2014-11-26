#ifndef BRUSH_H
#define BRUSH_H

#include "graphics/scene.h"
#define M_PI	3.14159265358979323846	/* pi */


class Brush : public Scene
{
public:
    Brush();

    QString name() { return "Brush"; }

    void setup();
    void paint();
    void resize();
    void action(int id);

private:
    QString mode;

    Color backColor;

    Color lineColor;
    int lineSize;
    int lineLimit;

    Color blotColor;
    Image *blotImages[10];
    int blotSize;
    int blotLimit;


};

#endif // BRUSH_H
