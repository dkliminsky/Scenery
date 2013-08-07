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

private:
    int maxFractal;
    Image *imageLine;

    bool isBezier;

    struct Fractal {
        float x1;
        float y1;
        float x2;
        float y2;
        QVector<Fractal> fractals;
    };
    QVector<Fractal> fractals;

    void createPoints(QVector<Fractal> &fractals);
    void createFractals(QVector<Fractal> &fractalsPattern, QVector<Fractal> &fractals, int deep=1);

    void drawLinks(QVector<Fractal> &fractals);
    void drawFractals(QVector<Fractal> &fractals, int maxDeep=1, int deep=1);

};

#endif // FRACTALS_H
