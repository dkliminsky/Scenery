#ifndef EFFECT03_H
#define EFFECT03_H


#include "graphics/scene.h"

class Effect03 : public Scene
{
public:
    Effect03();

    QString name() { return "Effect 03 Netting"; }

    void setup();
    void resize();
    void paint();

private:
    double decrease;

    int flareSize;
    Color flareColor;
    Image *imageFlare;

    Color nettingLineColor;
    int nettingLineWidth;
    int nettingMinDistance;
    int nettingMaxDistance;

    Color contourLineColor;
    int contourLineWidth;

    struct NettingArea {
        float x;
        float y;
        bool used;
    };
    QVector<NettingArea> nettingsArea;

    struct ElementDraw {
        int type;
        int width;
        Color color;
        Image *image;
        float x1;
        float y1;
        float x2;
        float y2;
    };
    QList<ElementDraw> elementsDraw;


    void effectFlare();
    void effectNetting();
    void effectContour();
    void drawElements();

};

#endif // EFFECT03_H
