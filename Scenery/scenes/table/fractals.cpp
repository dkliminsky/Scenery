#include "fractals.h"

Fractals::Fractals()
{
    control(maxFractal=5, "Fractal Level", 1, 10);
    control(isBezier=false, "Bezier");
}

void Fractals::setup()
{

}

void Fractals::resize()
{
    background(0, 0, 0, 1);
}

void Fractals::paint()
{
    int width = process(0)->width();
    int height = process(0)->height();

    size(width, height);
    background(0, 0, 0, 0.05);

    createPoints(fractals);
    createFractals(fractals, fractals);

    lineWidth(3);
    color(0.1, 0.1, 0.1, 0.2);
    drawFractals(fractals, maxFractal-2);

    lineWidth(2);
    color(0.5, 0.5, 0.5, 0.3);
    drawFractals(fractals, maxFractal-1);

    lineWidth(1);
    color(1, 1, 1, 1);
    drawFractals(fractals, maxFractal);

    lineWidth(1);
    color(0.3, 0, 0, 1);
    drawLinks(fractals);
}

void Fractals::createPoints(QVector<Fractals::Fractal> &fractals)
{
    fractals.clear();
    Fractal fractal;

    int count = 0;
    for(int i=0; i<10; i++) {
        if (process(i)->seqAreas().size() > 0 &&
            process(i)->seqAreas().at(0).number > 0) {
            float x = process(i)->seqAreas().at(0).pt[0];
            float y = process(i)->seqAreas().at(0).pt[1];

            if (count == 0) {
                fractal.x1 = x;
                fractal.y1 = y;
            }
            else if (count == 1) {
                fractal.x2 = x;
                fractal.y2 = y;
                fractals += fractal;
            }
            else {
                fractal.x1 = fractal.x2;
                fractal.y1 = fractal.y2;
                fractal.x2 = x;
                fractal.y2 = y;
                fractals += fractal;
            }
            count++;
        }
    }
}

void Fractals::createFractals(QVector<Fractal> &fractalsPattern, QVector<Fractal> &fractals, int deep)
{
    if (deep == maxFractal)
        return;

    if (fractalsPattern.size() == 0)
        return;

    float dPattern = distance(fractalsPattern.first().x1, fractalsPattern.first().y1,
                              fractalsPattern.last().x2,  fractalsPattern.last().y2);
    float aPattern = -angle(fractalsPattern.first().x1, fractalsPattern.first().y1,
                            fractalsPattern.last().x2,  fractalsPattern.last().y2);
    float x0Pattern = fractalsPattern.first().x1;
    float y0Pattern = fractalsPattern.first().y1;

    for (int i=0; i<fractals.size(); i++) {
        const Fractal &fractal = fractals.at(i);

        float dPart = distance(fractal.x1, fractal.y1, fractal.x2, fractal.y2);
        float k = dPart / dPattern;
        float a = - angle(fractal.x1, fractal.y1, fractal.x2, fractal.y2) - aPattern;

        for (int j=0; j<fractalsPattern.size(); j++) {
            const Fractal &fractalPattern = fractalsPattern.at(j);

            Fractal newFractal;
            float x1 = (fractalPattern.x1 - x0Pattern) * k;
            float y1 = (fractalPattern.y1 - y0Pattern) * k;
            float x2 = (fractalPattern.x2 - x0Pattern) * k;
            float y2 = (fractalPattern.y2 - y0Pattern) * k;

            newFractal.x1 = x1*cos(a) - y1*sin(a) + fractal.x1;
            newFractal.y1 = x1*sin(a) + y1*cos(a) + fractal.y1;
            newFractal.x2 = x2*cos(a) - y2*sin(a) + fractal.x1;
            newFractal.y2 = x2*sin(a) + y2*cos(a) + fractal.y1;

            fractals[i].fractals.append(newFractal);
        }

        createFractals(fractalsPattern, fractals[i].fractals, deep + 1);
    }
}

void Fractals::drawLinks(QVector<Fractals::Fractal> &fractals)
{
    for  (int i=0; i<fractals.size(); i++) {
        const Fractal &fractal = fractals.at(i);
        line(fractal.x1, fractal.y1, fractal.x2, fractal.y2);
    }
}

void Fractals::drawFractals(QVector<Fractal> &fractals, int maxDeep, int deep)
{
    if (maxDeep < 1)
        return;

    if (isBezier && deep == maxDeep && fractals.size() == 3) {
        lineParts(10);
        bezier(fractals.at(0).x1, fractals.at(0).y1, fractals.at(1).x1, fractals.at(1).y1,
               fractals.at(2).x1, fractals.at(2).y1, fractals.at(2).x2, fractals.at(2).y2);
    }

    for  (int i=0; i<fractals.size(); i++) {
        const Fractal &fractal = fractals.at(i);

        if (!isBezier && deep == maxDeep) {
            line(fractal.x1, fractal.y1, fractal.x2, fractal.y2);
        }

        drawFractals(fractals[i].fractals, maxDeep, deep + 1);
    }
}

