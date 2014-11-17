#ifndef SHADOWSCENE_H
#define SHADOWSCENE_H

#include "nodes/graphics/scene.h"


class ShadowScene : public Scene
{
public:
    ShadowScene();

    QString name() { return "Welcome"; }

    void setup();
    void resize();
    void paint();

private:
    Image imageShadow;
    int shadow_width;
    int shadow_height;
    int shadow_shift;
};

#endif // SHADOWSCENE_H
