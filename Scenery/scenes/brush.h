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
    Image *imgStroke;
    Image *imgLine;
    int speedLimit;
    int strokeWidth;

    struct Stroke {
        Point pt;
        float width;
        float height;
        float angle;
        Color color;
    };

    QVector<Stroke> strokes;
};

#endif // BRUSH_H
