#ifndef STRINGS_H
#define STRINGS_H

#include "graphics/scene.h"

class Strings : public Scene
{
public:
    Strings();

    QString name() { return "Strings"; }

    void setup();
    void paint();

private:
    Image *lineImage;
    Color backColor;
    Color color1;
    Color color2;

    double height1;
    double height2;
    int count;
    int frequency;
    int Amax;
    double force;
    double damping;

    struct String {
        float a;
        float dx;
        float dxPrev;
        int direction;

        float x1;
        float y1;
        float x2;
        float y2;
        float x3;
        float y3;
        float x4;
        float y4;
    };

    QVector<String> strings;
    bool debug;
    QString state;
};

#endif // STRINGS_H
