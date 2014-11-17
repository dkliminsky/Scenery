#include "shadowscene.h"

ShadowScene::ShadowScene()
{
    control(shadow_width=200, "shadow_width", 0, 200);
    control(shadow_height=200, "shadow_height", 0, 200);
    control(shadow_shift=50, "shadow_shift", -200, 200);
}

void ShadowScene::setup()
{
}

void ShadowScene::resize()
{
    background(1, 1, 1, 1);
}

void ShadowScene::paint()
{
    size(200, 200);
    background(1, 1, 1, 1);

    color(1, 1, 1, 1);
    imageShadow.set(process(0)->mat);
    imageShadow.bind();
    image(&imageShadow, 100 + shadow_shift, (200 - shadow_height) + (shadow_height / 2), shadow_width, shadow_height);
}
