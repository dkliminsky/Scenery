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
    int minDistance;
    int maxDistance;

    Color nettingLineColor;
    double nettingDecrease;
    int nettingLineWidth;

    struct ElementArea {
        float x;
        float y;
        bool used;
    };

    QVector<ElementArea> elementsArea;

    struct ElementDraw {
        int type;
        Color color;
        float x1;
        float y1;
        float x2;
        float y2;
    };

    QVector<ElementDraw> elementsDraw;




};

#endif // DANCEEFFECTS_H
