#ifndef DEFAULTSCENE_H
#define DEFAULTSCENE_H

#include "nodes/graphics/scene.h"


class DefaultScene : public Scene
{
public:
    DefaultScene();

    QString name() { return "Welcome"; }

    void setup();
    void resize();
    void paint();

private:
    Image *imageShip;
    Image *imageStream;

};

#endif // DEFAULTSCENE_H
