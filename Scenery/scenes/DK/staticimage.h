#ifndef STATICIMAGE_H
#define STATICIMAGE_H

#include "graphics/scene.h"


class StaticImage : public Scene
{
public:
    StaticImage();
    QString name() { return "Static Image"; }

    void setup();
    void paint();

private:
    Image *imageStatic;

};

#endif // STATICIMAGE_H
